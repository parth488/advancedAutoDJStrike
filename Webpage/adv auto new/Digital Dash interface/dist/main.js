// const dbRef = firebase.database().ref();
   var x;
var startstop = 0;

function startStop() { /* Toggle StartStop */

  startstop = startstop + 1;

  if (startstop === 1) {
    start();
    document.getElementById("cir2").innerHTML = "Stop";
  } else if (startstop === 2) {
    document.getElementById("cir2").innerHTML = "Start";
    startstop = 0;
    stop();
  }

}

var gearc=0;
function incrementgear(){

  if(gearc>=6){
     gearc=6;
      }
  else{

        gearc=gearc;
      
  document.getElementById("gear-text").innerHTML = gearc+=1;
  }
  

}

function decrementgear(){
  
  if(gearc<=1){
    
    document.getElementById("gear-text").innerHTML = "N";
  }
  
  else{
    gearc-=1;
    document.getElementById("gear-text").innerHTML = gearc;}
}






var speedinc=0;
   function increasespeed() {
    
    
    document.getElementById("speed-text").innerHTML = speedinc+=1;


    
    
    
    for (var k = 1; k <=7; k++) {
      (function (k) {
        setTimeout(function () {
         
         var str1 = "b";
         var str4 = k;
         var res4 = str1.concat(str4);   
         document.getElementById(res4).style.opacity="1";},60*k);})(k);
         
         }
 var boost1 = [7,6,5,4,3,2,1];
       for (let z = 0; z<= 7; z++) {
          (function (z) {
            setTimeout(function () {
             
             var str1 = "bb";
             var str3 = boost1[z];
             var str2 = str3.toString();
             // console.log(str2)
 
             res5 = str1.concat(str2); 
              
             document.getElementById(res5).style.opacity="0.2";},60*z);})(z);}
  }
  
  
  
  
  function decreasespeed() {
    if(speedinc<=0){
      speedinc=0;
    }
    else{
    document.getElementById("speed-text").innerHTML = speedinc-=1;}
    
    for (var k = 1; k <=7; k++) {
      (function (k) {
        setTimeout(function () {
         
         var str1 = "bb";
         var str4 = k;
         var res4 = str1.concat(str4);   
         document.getElementById(res4).style.opacity="1";},60*k);})(k);
         
  }


 
 


    var boost1 = [7,6,5,4,3,2,1];
       for (let z = 0; z<= 7; z++) {
          (function (z) {
            setTimeout(function () {
             
             var str1 = "b";
             var str3 = boost1[z];
             var str2 = str3.toString();
             // console.log(str2)
 
             res5 = str1.concat(str2); 
              
             document.getElementById(res5).style.opacity="0.3";},60*z);})(z);}
    
  }


  
getData();

function getData() {
  // body...LDRLightLevel
  firebase.database().ref('Sensors/DHT11/').on('value',(snap)=>{
          // console.log(snap.val());
          firebasenum = snap.val();
          document.getElementById("number90").innerHTML = firebasenum.Humidity;
          
          document.getElementById("number78").innerHTML = firebasenum.Temperature;
        });
  firebase.database().ref('Sensors/LDRLightLevel/').on('value',(snap)=>{
          // console.log(snap.val());
          firebasenum = snap.val();
          console.log(firebasenum);
          if (firebasenum===1) {
            elements = document.getElementsByClassName("divclass");
         for (var i = 0; i < elements.length; i++) {
        elements[i].style.backgroundColor="transparent";
    }
          }
          else{
            elements = document.getElementsByClassName("divclass");
         for (var i = 0; i < elements.length; i++) {
        elements[i].style.backgroundColor="black";

          }}
        });
}
function start() {
  x = setInterval(timer, 10);
} /* Start */

function stop() {
  clearInterval(x);
} /* Stop */

var milisec = 0;
var sec = 0; /* holds incrementing value */
var min = 0;
var hour = 0;

/* Contains and outputs returned value of  function checkTime */

var miliSecOut = 0;
var secOut = 0;
var minOut = 0;
var hourOut = 0;

/* Output variable End */


function timer() {
  /* Main Timer */


  miliSecOut = checkTime(milisec);
  secOut = checkTime(sec);
  minOut = checkTime(min);
  hourOut = checkTime(hour);

  milisec = ++milisec;

  if (milisec === 100) {
    milisec = 0;
    sec = ++sec;
  }

  if (sec == 60) {
    min = ++min;
    sec = 0;
  }

  if (min == 60) {
    min = 0;
    hour = ++hour;

  }


  document.getElementById("milisec").innerHTML = miliSecOut;
  document.getElementById("sec").innerHTML = secOut;
  document.getElementById("min").innerHTML = minOut;
  document.getElementById("hour").innerHTML = hourOut;

}


/* Adds 0 when value is <10 */


function checkTime(i) {
  if (i < 10) {
    i = "0" + i;
  }
  return i;
}

function reset() {


  /*Reset*/

  milisec = 0;
  sec = 0;
  min = 0
  hour = 0;

  document.getElementById("milisec").innerHTML = "00";
  document.getElementById("sec").innerHTML = "00";
  document.getElementById("min").innerHTML = "00";
  document.getElementById("hour").innerHTML = "00";

}

   function startTime() {
    var today = new Date();
    var h = today.getHours();
    var m = today.getMinutes();
    var s = today.getSeconds();
    m = checkTime(m);
    s = checkTime(s);
    document.getElementById('row4').innerHTML =
    h + ":" + m + ":" + s;
    var t = setTimeout(startTime, 500);
  }
  function checkTime(i) {
    if (i < 10) {i = "0" + i};  // add zero in front of numbers < 10
    return i;
  }





  
   var gearcounter=['N',1,2,3,4,5,6];
   var upgear=0;




   function myEnterFunction() {
    upgear+=1;
    if(upgear<=6){
      
      var counter = gearcounter[upgear]
      document.getElementById("gear-text").innerHTML = counter;
      
        }
        else{
          document.getElementById("gear-text").innerHTML = 6;
          upgear=6;
        }
      

  }

  

  function myEnterFunction2() {
    document.getElementById("gear-text").innerHTML = upgear-=1;
    if(upgear<=0){
      
      upgear=0;
      document.getElementById("gear-text").innerHTML = "N";
    }
    
  }
  

  
    
    function revincrease() {
      // need shift key pressed
      
      for (var j = 1; j <=35; j+=2) {
         (function (j) {
           setTimeout(function () {
            
            var str1 = "l";
            var str4 = j;
            var res1 = str1.concat(str4);   
            document.getElementById(res1).style.opacity="1";},4*j);})(j);
          
            
           }}

           function revdecrease(){
            // need shift key released
            
            var lights = [35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1];
               for (let i = 0; i<= 34; i+=2) {
                  (function (i) {
                    setTimeout(function () {
                     var res="";
                     var str1 = "l";
                     var str3 = lights[i];
                     var str2 = str3.toString();
                     // console.log(str2)
         
                     res = str1.concat(str2); 
                      
                     document.getElementById(res).style.opacity="0.1";},20*i);})(i);}
          
          }


  
   


  
  function screenload(){
    document.getElementById("screenstart").style.animation = "fadeLoad ease 5s";
    document.getElementById("screenstart").style.animationIterationCount = "infinite";
    
  }
  var inccount=0;
function power(){
  inccount+=1
  
  if(inccount%2==0){
    document.getElementById("digitalgrid").style.opacity= 0.0;
    document.getElementById("screenstart").style.display="block";
    document.getElementById("screenstart").style.animation = "fadeIn ease 6s";
  }
  else{
    document.getElementById("digitalgrid").style.opacity = 0.9;
    
    document.getElementById("screenstart").style.animation = "fadeOut ease 6s";
    document.getElementById("screenstart").style.display="none";
    
  }

document.getElementById("cir1").style.fill= "yellow";
document.getElementById("cir1").style.opacity= 0.9;


}
var tcount=0;
function tcsetting(){
  tcount+=1;
  var str1 = "bbb";
  var str4 = tcount;
  var res4 = str1.concat(str4);   
  document.getElementById(res4).style.opacity="1";

}
