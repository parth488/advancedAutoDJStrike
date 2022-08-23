$("#test3").on({
    keydown: function(f) {
      if(f.originalEvent.key === "b")
        thirdcalled();
    },
    keyup: function(f) {
      if (f.originalEvent.key === "b")
        
        thirdcalled_another_func();
    },
    keypress: function() {
      console.log('keypress triggered')
    }
  })
  
  function thirdcalled() {
    // need shift key pressed
    for (var k = 1; k <=7; k++) {
       (function (k) {
         setTimeout(function () {
          
          var str1 = "bbb";
          var str4 = k;
          var res4 = str1.concat(str4);   
          document.getElementById(res4).style.opacity="1";},20*k);})(k);
          if(k==7){
            break;
            
          }
          
          
           
  }}
  
  function thirdcalled_another_func() {
    // need shift key released
    
    var boost1 = [7,6,5,4,3,2,1];
       for (let z = 0; z<= 7; z++) {
          (function (z) {
            setTimeout(function () {
             
             var str1 = "bbb";
             var str3 = boost1[z];
             var str2 = str3.toString();
             // console.log(str2)
 
             res5 = str1.concat(str2); 
              
             document.getElementById(res5).style.opacity="0.2";},10*z);})(z);}
  
  }