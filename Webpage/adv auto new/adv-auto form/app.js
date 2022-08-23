// Initialize firebase
var firebaseConfig = {
    apiKey: "AIzaSyBC7IQnZ6eIkw57YKH8XGKIJ-UwLeuRD44",
    authDomain: "advanced-auto-7de27.firebaseapp.com",
    databaseURL: "https://advanced-auto-7de27.firebaseio.com",
    projectId: "advanced-auto-7de27",
    storageBucket: "advanced-auto-7de27.appspot.com",
    messagingSenderId: "684885116976",
    appId: "1:684885116976:web:82a1d4b31780e6e5c005f5",
    measurementId: "G-5VBHGYEYR3"
};
firebase.initializeApp(firebaseConfig);
const dbRef = firebase.database().ref();
const usersRef = dbRef.child('name');
var email2;




  function writeData(){
        firebase.database().ref("name").push({
      manufacturer: document.getElementById("manufactureField").value,
      name: document.getElementById("nameField").value,
      color: document.getElementById("colorField").value,
      licence: document.getElementById("licenceField").value,
      type: document.getElementById("typeField").value,
        number: document.getElementById("numberField").value,
        email: document.getElementById("emailField").value
          });

        email2= document.getElementById("emailField").value
        
  }

  function show(){

function getdata(){

    firebase.database().ref("name").once('value', function(snapshot) {
      snapshot.forEach(function(childSnapshot)
      {
        var childKey = childSnapshot.key;
        var childData = childSnapshot.val();
        document.getElementById("data").innerHTML=childData['color'] + "," +childData['type'] + "," +childData['licence'];
      })
    })
  }
getdata();

  }

var email_id;
// onAuthStateChanged will be called when the authentication state changes
// that is when the user is logged in
firebase.auth().onAuthStateChanged(function(user) {
  if (user) {
    // User is signed in.
    document.getElementById("user_div").style.display = "block";
    // get the currentUser who is logged in
    var user = firebase.auth().currentUser;
    // if user is present
    if(user != null){
      // set email
      window.location.href = "advauto.html";
      email_id = user.email;
      // redirect to the homepage
    }
  }
});

function signup(){
  // get the email
  userEmail = document.getElementById("email_field").value;
  // get the password
  userPass = document.getElementById("password_field").value;
  // get the confirm password value
  userConfirmPass = document.getElementById("confirm_password_field").value;
  // if first and second passwords match
  if (userPass === userConfirmPass) {
    // create a user with the given email and password
  	firebase.auth().createUserWithEmailAndPassword(userEmail, userPass).then(cred => {
      // then signout so that we can redirect back to login page
      firebase.auth().signOut();
      alert('User signed up!');
      window.location.href = "login.html";
  });
  } else {
    // if password and confirm password values don't match then empty those fields
  	document.getElementById("password_field").value = "";
  	document.getElementById("confirm_password_field").value = "";
  	alert('Passwords do not match!');
  }
}

function login(){
  // get the email
  userEmail = document.getElementById("email_field").value;
  // get the password
  userPass = document.getElementById("password_field").value;
  // pass them to firebase so that we can login
  if (userEmail != "" || userPass != "") {
    firebase.auth().signInWithEmailAndPassword(userEmail, userPass)
  .catch(function(error) {
    // Handle Errors here.
    // if there is any error like user does not exist then we will catch and display it here
    var errorCode = error.code;
    var errorMessage = error.message;
    window.alert("Error : " + errorMessage);
  });
}else{
  window.alert("Please fill all the fields.");
}
  

}
var otpnum, recivedotp;
function new1(){
  current_author = firebase.auth().currentUser.email;
  console.log(current_author);
    otpnum = (Math.floor(Math.random() * 1000000));
    
    Email.send({ 
        Host: "smtp.gmail.com", 
        Username: "advancedauto9899@gmail.com", 
        Password: "advauto@vln98", 
        To: current_author, 
        From: "advancedauto9899@gmail.com", 
        Subject: "Sending Email using javascript", 
        Body: "Your Otp is : " + otpnum, 
    }) 
        .then(function (message) { 
        alert("mail sent successfully") 
        }); 
       
        firebase.database().ref("name/otp").push({
          author: current_author,
          otpnum: otpnum
        })
        firebase.database().ref("Validation/sent").set(
            otpnum
        )
}

function logout(){
  // signout of the session from firebase
  firebase.auth().signOut();
  // redirect back to the login page
  window.location.href = "login.html";
}
function getEmail(){
  
}


// otp
var newemail, email, current_author;
function sendOTP() { 
  recivedotp = document.getElementById("otpnum").value;
  firebase.database().ref("Validation/received").set(
          Number(recivedotp))
  document.getElementById("otpnum").value="";
  alert("otp sent successfully");
    } 


