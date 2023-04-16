const scriptURL =
  "https://script.google.com/macros/s/AKfycbxGwOLT6hY8_wWa4dhnmq63ZBhdqEFJlqKksVa3IsChnkMW9UIj-pv-HSiURVIP17z9/exec";
const form = document.forms["testJIG"];

const validUsers = ["Aniket Apraj", "Omkar Pol", "Ronit Suryarao","Leticia Jacob"];

form.addEventListener("submit", e => {
  e.preventDefault();
  const userName = form.elements["Name"].value;
  if (!validUsers.includes(userName)) {
    alert("You are not authorized to do this test!!");
    return;
  }
  fetch(scriptURL, { method: "POST", body: new FormData(form) })
    .then(response => alert("Submitted Know you can start the test!!"))
    .catch(error => console.error("Error!", error.message));
  document.getElementById("myForm").reset();
});


// async function fetchValidUsers() {
//   const scriptURL =
//     "https://script.google.com/macros/s/AKfycbxGwOLT6hY8_wWa4dhnmq63ZBhdqEFJlqKksVa3IsChnkMW9UIj-pv-HSiURVIP17z9/exec";
//   const response = await fetch(sheetUrl);
//   const form = document.forms["testJIG"];
//   const data = await response.json();
//   const validUsers = data.values.map(row => row[0]);
//   return validUsers;
// }

// fetchValidUsers();
// const form = document.forms["testJIG"];
// form.addEventListener("submit", async e => {
//   e.preventDefault();
//   const userName = form.elements["Name"].value;
//   const validUsers = await fetchValidUsers();
//   if (!validUsers.includes(userName)) {
//     alert("You are not authorized to fill this form.");
//     return;
//   }
//   fetch(scriptURL, { method: "POST", body: new FormData(form) })
//     .then(response => alert("Submitted Know you can start the test!!"))
//     .catch(error => console.error("Error!", error.message));
//   document.getElementById("myForm").reset();
// });
