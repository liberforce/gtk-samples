#!/usr/bin/env python
##    cairo demos Copyright (C)  2007 Donn.C.Ingle
##
##    Contact: donn.ingle@gmail.com - I hope this email lasts.
##
##    This program is free software; you can redistribute it and/or modify
##    it under the terms of the GNU General Public License as published by
##    the Free Software Foundation; either version 2 of the License, or
##    (at your option)  any later version.
##
##    This program is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU General Public License for more details.
##
##    You should have received a copy of the GNU General Public License
##    along with this program; if not, write to the Free Software
##    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

import cairo
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, Gdk, GObject


class Screen(Gtk.DrawingArea):
    """ This class is a Drawing Area"""
    def __init__(self):
        super(Screen,self).__init__()
        ## Connect to the "draw" signal
        self.connect("draw", self.on_draw)
        ## This is what gives the animation life!
        GObject.timeout_add(50, self.tick) # Go call tick every 50 whatsits.

    def tick(self):
        ## This invalidates the screen, causing the "draw" event to fire.
        rect = self.get_allocation()
        self.get_window().invalidate_rect(rect, True)
        return True # Causes timeout to tick again.

    ## When the "draw" event fires, this is run
    def on_draw(self, widget, event):
        self.cr = self.get_window().cairo_create()
        ## Call our draw function to do stuff.
        geom = self.get_window().get_geometry()
        self.draw(geom.width, geom.height)

class MyStuff(Screen):
    """This class is also a Drawing Area, coming from Screen."""
    def __init__(self):
        Screen.__init__(self)
        ## x,y is where I'm at
        self.x, self.y = 25, -25
        ## rx,ry is point of rotation
        self.rx, self.ry = -10, -25
        ## rot is angle counter
        self.rot = 0
        ## sx,sy is to mess with scale
        self.sx, self.sy = 1, 1

    def draw(self, width, height):
        ## A shortcut
        cr = self.cr

        ## First, let's shift 0,0 to be in the center of page
        ## This means:
        ##  -y | -y
        ##  -x | +x
        ## ----0------
        ##  -x | +x
        ##  +y | +y

        matrix = cairo.Matrix(1, 0, 0, 1, width/2, height/2)
        cr.transform(matrix) # Make it so...

        ## Now save that situation so that we can mess with it.
        ## This preserves the last context(the one at 0,0)
        ## and let's us do new stuff.
        cr.save()

        ## Now attempt to rotate something around a point
        ## Use a matrix to change the shape's position and rotation.

        ## First, make a matrix. Don't look at me, I only use this stuff :)
        ThingMatrix = cairo.Matrix(1, 0, 0, 1, 0, 0)

        ## Next, move the drawing to it's x,y
        cairo.Matrix.translate(ThingMatrix, self.x, self.y)
        cr.transform(ThingMatrix) # Changes the context to reflect that

        ## Now, change the matrix again to:
        cairo.Matrix.translate(ThingMatrix, self.rx, self.ry) # move it all to point of rotation
        cairo.Matrix.rotate(ThingMatrix, self.rot) # Do the rotation
        cairo.Matrix.translate(ThingMatrix, -self.rx, -self.ry) # move it back again
        cairo.Matrix.scale(ThingMatrix, self.sx, self.sy) # Now scale it all
        cr.transform(ThingMatrix) # and commit it to the context

        ## Now, whatever is draw is "under the influence" of the
        ## context and all that matrix magix we just did.
        self.drawCairoStuff(cr)

        ## Let's inc the angle a little
        self.rot += 0.1

        ## Now mess with scale too
        self.sx += 0 # Change to 0 to see if rotation is working...
        if self.sx > 4: self.sx=0.5
        self.sy = self.sx

        ## We restore to a clean context, to undo all that hocus-pocus
        cr.restore()

        ## Let's draw a crosshair so we can identify 0,0
        ## Drawn last to be above the red square.
        self.drawcross(cr)

    def drawCairoStuff(self, cr):
        ## Thrillingly, we draw a red rectangle.
        ## It's drawn such that 0,0 is in it's center.
        cr.rectangle(-25, -25, 50, 50)
        cr.set_source_rgb(1, 0, 0)
        cr.fill()
        ## Now a visual indicator of the point of rotation
        ## I have no idea(yet) how to keep this as a
        ## tiny dot when the entire thing scales.
        cr.set_source_rgb(1, 1, 1)
        cr.move_to(self.rx, self.ry)
        cr.line_to(self.rx+1, self.ry+1)
        cr.stroke()

    def drawcross(self, ctx):
        ## Also drawn around 0,0 in the center
        ctx.set_source_rgb(0, 0, 0)
        ctx.move_to(0,10)
        ctx.line_to(0, -10)
        ctx.move_to(-10, 0)
        ctx.line_to(10, 0)
        ctx.stroke()


def run(Widget):
    window = Gtk.Window()
    window.connect("destroy", Gtk.main_quit)
    window.set_size_request(400, 400)
    widget = Widget()
    widget.show()
    window.add(widget)
    window.present()
    Gtk.main()

run(MyStuff)
