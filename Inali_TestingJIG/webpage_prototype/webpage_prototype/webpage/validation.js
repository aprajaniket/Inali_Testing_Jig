var validUsers = ["Aniket", "Ronit", "Omkar"];

//form validation function
function validateForm() {
  //get the entered name
  var name = document.forms["testJIG"]["name"].value;

  //check if the entered name is in the list of valid users
  if(validUsers.indexOf(name) === -1) {
    alert("Sorry, you are not authorized to fill this form");
    return false;
  }
  return true;
}

//attach the validation function to the form's submit event
var form = document.getElementById("testJIG");
form.addEventListener("submit", function (event) {
  event.preventDefault();
  if (validateForm()) {
    form.submit();
  }
});
