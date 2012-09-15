
// Sunrise.js
// Sunrise Algotithm

//Source:
//	Almanac for Computers, 1990
//	published by Nautical Almanac Office
//	United States Naval Observatory
//	Washington, DC 20392

//Inputs:
//	day, month, year:      date of sunrise/sunset
//	latitude, longitude:   location for sunrise/sunset
//	zenith:                Sun's zenith for sunrise/sunset
//	  offical      = 90 degrees 50'
//	  civil        = 96 degrees
//	  nautical     = 102 degrees
//	  astronomical = 108 degrees

// inlets and outlets
inlets = 3;
outlets = 2;

// global variables
var x = 0.66;

// calculate the time of the sunset
function Sunrise(day,month,year)
{
	var zenith = 90.85;
	
	//1. first calculate the day of the year

	var N1 = floor(275 * month / 9);
	var N2 = floor((month + 9) / 12);
	var N3 = (1 + floor((year - 4 * floor(year / 4) + 2) / 3));
	var N = N1 - (N2 * N3) + day - 30;
	
	//2. convert the longitude to hour value and calculate an approximate time

	lngHour = longitude / 15;
	t = N + ((6 - lngHour) / 24);
	
	//3. calculate the Sun's mean anomaly
	
	var M = (0.9856 * t) - 3.289;

	//4. calculate the Sun's true longitude
	
	var L = M + (1.916 * sin((pi/180)*M)) + (0.020 * sin((pi/180)i*2 * M)) + 282.634;
	//NOTE: L potentially needs to be adjusted into the range [0,360) by adding/subtracting 360

	//5a. calculate the Sun's right ascension
	
	var RA = (180/pi)*atan(0.91764 * tan((pi/180)*L));
	//NOTE: RA potentially needs to be adjusted into the range [0,360) by adding/subtracting 360

	//5b. right ascension value needs to be in the same quadrant as L

	var Lquadrant  = (floor( L/90)) * 90;
	var RAquadrant = (floor(RA/90)) * 90;
	RA = RA + (Lquadrant - RAquadrant);

	//5c. right ascension value needs to be converted into hours

	RA = RA / 15;

	//6. calculate the Sun's declination

	sinDec = 0.39782 * sin((pi/180)*L);
	cosDec = cos(asin((pi/180)*sinDec)); //CHECK!!!!

	//7a. calculate the Sun's local hour angle
	
	cosH = (cos((pi/180)*zenith) - (sinDec * sin((pi/180)*latitude))) / (cosDec * cos((pi/180)*latitude))
	
	if (cosH >  1) 
	  post.("the sun never rises on this location (on the specified date)");
	if (cosH < -1)
	   post.("the sun never sets on this location (on the specified date)");

	//7b. finish calculating H and convert into hours
	
	H = 360 - acos(cosH); //CHECK
	H = H / 15;

	//8. calculate local mean time of rising/setting
	
	T = H + RA - (0.06571 * t) - 6.622;

	//9. adjust back to UTC
	
	UT = T - lngHour;
	//NOTE: UT potentially needs to be adjusted into the range [0,24) by adding/subtracting 24

	//10. convert UT value to local time zone of latitude/longitude
	
	localT = UT + localOffset;
	
	x = r*x*(1.-x);
	outlet(0, x);
}

// bang -- post the current population to the max window
function bang()
{
	post("the current population is");
	post(x);
	post();
}