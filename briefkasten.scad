fn = 64;

difference(){
	
	//Semisphere
    hull() {
        sphere(r=40, $fn=4*fn);
        translate([0, 0, 18]) sphere(r=40, $fn=4*fn);
    }
    translate([-40,0,-40]){
		cube(size=200);
    }
    translate([-5,-21,5]){   
        translate([-15,-6,-26]){
            cube([9,28,52]);
        }
    }
    
	
    translate([-7.5,-25.5,-16]){
		cube([15,25,32]);
		translate([12.5-1.5,0,29.5-0.5])rotate([90,0,0]) cylinder(h=15,d=5.5, $fn=fn);
		translate([4,0,29.5-0.5])rotate([90,0,0]) cylinder(h=15,d=5.5, $fn=fn);
		translate([8,0,32-19])rotate([90,0,0]) cube([7,7,20]);    
    }
    
	
	translate([18,-8,-31]){
		union(){
			cylinder(h=70,d=9, $fn=fn);
			translate([-4,0,2])cube([9,20,62]);   
        }
	};
   
	translate([-10,-20,-32]){
		cube([21,20,80]);
	}

	translate([-15,-25,-5])rotate([0,90,0]) cylinder(h=25, r=2, $fn=4*fn);
	translate([-30,-80,-40]) cube([70,50,100]);

	translate([0,18,-10])difference(){
		rotate([90])cylinder(h=20, r=28, $fn=2*fn);
		rotate([90])cylinder(h=20, r=26, $fn=2*fn);
		translate([-40,-25,-18]) cube([80,30,40]);
    }
    
   translate([-21,-5,-28.2]) cube([2.5,5,20]);  
}