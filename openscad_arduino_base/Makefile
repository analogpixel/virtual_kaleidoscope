bin=/Applications/OpenSCAD.app/Contents/MacOS/OpenSCAD
fn=base1.scad

define create-part
	$(bin) -o $(@).stl $(fn)
endef

# _bigBox : box that can hold other boxes
# _smallBox : fits into bigBox

open:
	$(bin) $(fn)

arduino_base:
	$(create-part) -D "_arduino_base=true"

all: arduino_base

clean:
	rm *.stl
