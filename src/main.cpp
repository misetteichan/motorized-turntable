// Copyright (c) 2025 misetteichan
// Licensed under the MIT License. See LICENSE file for details.

#include <M5Unified.h>
#include <unit_rolleri2c.hpp>
#include <deque>

class MovingAverage {
  const size_t size;
  int64_t sum;
  std::deque<int32_t> values;
public:
  explicit MovingAverage(size_t size) : size(size), sum(0) {}

  int32_t add(int32_t value) {
    if (values.empty() || std::abs(value - values.back()) < 1000000) {
      values.push_back(value);
      sum += value;
      if (values.size() > size) {
        sum -= values.front();
        values.pop_front();
      }
    }
    return get();
  }

  int32_t get() const {
    return values.empty() ? 0 : sum / values.size();
  }
};


class Roller {
  UnitRollerI2C _roller;
  bool _running = false;
  int32_t _speed = 0;
public:
  void begin() {
    const auto sda = M5.getPin(m5::pin_name_t::port_a_sda);
    const auto scl = M5.getPin(m5::pin_name_t::port_a_scl);
    while(!_roller.begin(&Wire, 0x65, sda, scl)) {
      M5_LOGE("Failed to initialize roller");
      delay(500);
    }
    _roller.setRGBMode(roller_rgb_t::ROLLER_RGB_MODE_USER_DEFINED);
    _roller.setRGB(0);
    _roller.resetStalledProtect();
    _roller.setOutput(0);
    _roller.setSpeedMaxCurrent(100000);
    _roller.setMode(ROLLER_MODE_SPEED);
    _running = false;
  }

  bool isRunning() const {
    return _running;
  }

  void start(int32_t speed) {
    _roller.setSpeed(speed);
    _roller.setOutput(1);
    _speed = speed;
    _running = true;
  }

  void stop() {
    _roller.setOutput(0);
    _running = false;
  }

  int32_t getSpeedReadback() {
    return _roller.getSpeedReadback();
  }

  int32_t getSpeed() const {
    return _running ? _speed : 0;
  }
};

Roller roller;
MovingAverage speed(5);

void setup() {
  M5.begin();
  roller.begin();
}

void loop() {
  static unsigned long begin_detect = 0;
  const auto current = speed.add(roller.getSpeedReadback()) / 100;

  if (roller.isRunning()) {
    const auto speed = std::abs(roller.getSpeed() / 100);
    const auto diff = std::abs(current - roller.getSpeed() / 100);
    if ((speed <= 5 && diff != 0) || (speed > 5 && diff >= 5)) {
      if (begin_detect == 0) {
        begin_detect = millis();
      }
    } else if (begin_detect != 0) {
      begin_detect = 0;
    }
  } else {
    if (current != 0 && begin_detect == 0) {
      begin_detect = millis();
    } else if (current == 0 && begin_detect != 0) {
      begin_detect = 0;
    }
  }
  if (begin_detect == 0) {
    return;
  }

  // 指定されている速度と実際の速度が異なり始めてからTms経過したら速度を指定し直す
  if (millis() - begin_detect >= (roller.isRunning() ? 100 : 500)) {
    if (std::abs(current) < 5) {
      roller.stop();
    } else {
      roller.start(current * 100);
    }
    begin_detect = 0;
  }
}
