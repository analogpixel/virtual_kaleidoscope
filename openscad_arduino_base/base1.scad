
difference() {

  union() {
    translate([0,0,5]) linear_extrude(10) square([60,80], true);
    linear_extrude(5) difference() {
      square([60,80], true);
      square([50,70], true);
    }
  }
  color("blue") translate([-25,-20,0]) linear_extrude(20) polygon( [ [0,0],[50/2, 50], [50,0]  ] );
}
