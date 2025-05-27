# Copyright (c) 2025 misetteichan
# Licensed under the MIT License. See LICENSE file for details.

from solid2 import *
from os import remove

set_global_fn(100)

def wall(diameter: int, height: int, thickness: int=1):
    return cylinder(h=height, r=diameter/2) - cylinder(h=height, r=(diameter/2) - thickness)


def main(diameter: int):
    model = cylinder(10, 10, 10)
    
    _roller = (cube(40, 40, 15.2).translate(-20, -20, 0) + cylinder(h=14.8,r=20).up(15.2)).color('gray')
    _roller += [cube(12.2, 5, 15.2).translate(-12.2/2, -20 -5, 0).color('white').rotateZ(r) for r in range(0,360,90)]
    _c6 = cube(12, 23.2, 9.5).translate(-12/2, diameter/2 - 23.2, 3).color('cyan')
    
    space = .5
    bottom = cube(50, 50, 15.2 - space).translate(-25, -25, 0) + wall(diameter, 15.2 - space)
    bottom += cylinder(h=2, r=diameter/2).translate(0, 0, -1)
    bottom += intersection()(
      cube(12+6, 12, 9.5+6).translate(-(12+6)/2, diameter/2 - 12, 0),
      cylinder(h=15.2 - space, r=diameter/2)
    )
    bottom -= _roller + _c6

    upper = [cube(diameter-1,2,6).translate(-(diameter-1)/2, -2/2, 0).rotateZ(r) for r in range(0,360,45)]
    upper += wall(diameter, 15.2-.5, 1).translate(0, 0, 0)
    upper += cylinder(h=9, r=41/2+2)
    upper += cylinder(h=3, r=diameter/2).translate(0, 0, -2)
    upper -= cylinder(h=9, r=41.5/2)
    bis = cylinder(h=1.8,r1=5.6/2,r2=3.2/2) + cylinder(h=10,r=3.2/2)
    bis = bis.translate(10, 0, -2)
    upper -= [bis.rotateZ(r) for r in range(0,360,90)]
    top = cylinder(h=1.8, r= diameter/2)

    model = bottom + _roller  + _c6
    model += upper.rotateY(180).up(15.2 + 15.2)
    model += top.up(15.2 + 15.2 + 3)
    model.save_as_scad()

    def save_as_stl(obj, filename):
        obj.save_as_stl(filename)
        remove(f'{filename}.scad')

    save_as_stl(top, 'top.stl')
    save_as_stl(bottom, 'bottom.stl')
    save_as_stl(upper, 'upper.stl')


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--diameter', type=int, default=100)
    args = parser.parse_args()
    main(args.diameter)
