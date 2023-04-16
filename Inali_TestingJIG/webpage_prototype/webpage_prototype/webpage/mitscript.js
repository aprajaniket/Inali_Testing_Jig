function doGet(e) {
  var ss = SpreadsheetApp.openByUrl(
    "https://docs.google.com/spreadsheets/d/19DaOkCe68KY3nZ3pY8KTbMAJkF-0RsDUMTkcHBt7B0s/edit#gid=0"
  );
  var sheet = ss.getSheetByName("Sheet1");

  addUser(e, sheet);
}

function doPost(e) {
  var ss = SpreadsheetApp.openByUrl(
    "https://docs.google.com/spreadsheets/d/19DaOkCe68KY3nZ3pY8KTbMAJkF-0RsDUMTkcHBt7B0s/edit#gid=0"
  );
  var sheet = ss.getSheetByName("Sheet1");

  addUser(e, sheet);
}

function addUser(e, sheet) {
  const validUsers = [
    "Aniket Apraj",
    "Omkar Pol",
    "Ronit Suryarao",
    "Leticia Jacob",
  ];
  var name = e.parameter.validUsers;
  var batch = e.parameter.batch;
  
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
    // document.getElementById("myForm").reset();

  });
  sheet.appendRow([name, batch]);
}


function doGet(e) {
  var ss = SpreadsheetApp.openByUrl(
    "https://docs.google.com/spreadsheets/d/19DaOkCe68KY3nZ3pY8KTbMAJkF-0RsDUMTkcHBt7B0s/edit#gid=0"
  );
  var sheet = ss.getSheetByName("Sheet1");

  addUser(e, sheet);
}

function doPost(e) {
  var ss = SpreadsheetApp.openByUrl(
    "https://docs.google.com/spreadsheets/d/19DaOkCe68KY3nZ3pY8KTbMAJkF-0RsDUMTkcHBt7B0s/edit#gid=0"
  );
  var sheet = ss.getSheetByName("Sheet1");

  addUser(e, sheet);
}

function addUser(e, sheet) {
  var name = e.parameter.name;
  var batch = e.parameter.batch;

  sheet.appendRow([name, batch]);
}







var SS = SpreadsheetApp.openById(
  "19DaOkCe68KY3nZ3pY8KTbMAJkF-0RsDUMTkcHBt7B0s"
);
var str = "";

function doPost(e) {
  var parsedData;
  var result = {};

  try {
    parsedData = JSON.parse(e.postData.contents);
  } catch (f) {
    return ContentService.createTextOutput(
      "Error in parsing request body: " + f.message
    );
  }

  if (parsedData !== undefined) {
    var flag = parsedData.format;
    if (flag === undefined) {
      flag = 0;
    }

    var sheet = SS.getSheetByName(parsedData.sheet_name); // sheet name to publish data to is specified in Arduino code
    var dataArr = parsedData.values.split(","); // creates an array of the values to publish

    var date_now = Utilities.formatDate(new Date(), "CST", "yyyy/MM/dd"); // gets the current date
    var time_now = Utilities.formatDate(new Date(), "CST", "hh:mm:ss a"); // gets the current time

    var value0 = dataArr[0]; // value0 from Arduino code
    var value1 = dataArr[1]; // value1 from Arduino code
    var value2 = dataArr[2]; // value2 from Arduino code
    var value3 = dataArr[3]; // value3 from Arduino

    // read and execute command from the "payload_base" string specified in Arduino code
    switch (parsedData.command) {
      case "insert_row":
        sheet.insertRows(2); // insert full row directly below header text

        //var range = sheet.getRange("A2:D2");              // use this to insert cells just above the existing data instead of inserting an entire row
        //range.insertCells(SpreadsheetApp.Dimension.ROWS); // use this to insert cells just above the existing data instead of inserting an entire row

        sheet.getRange("C2").setValue(date_now); // publish current date to cell A2
        sheet.getRange("D2").setValue(time_now); // publish current time to cell B2
        sheet.getRange("E2").setValue(value0); // publish value0 from Arduino code to cell C2
        sheet.getRange("F2").setValue(value1); // publish value1 from Arduino code to cell D2
        sheet.getRange("G2").setValue(value2); // publish value2 from Arduino code to cell E2
        sheet.getRange("H2").setValue(value3);

        str = "Success"; // string to return back to Arduino serial console
        SpreadsheetApp.flush();
        break;

      case "append_row":
        var publish_array = new Array(); // create a new array

        publish_array[0] = date_now; // add current date to position 0 in publish_array
        publish_array[1] = time_now; // add current time to position 1 in publish_array
        publish_array[2] = value0; // add value0 from Arduino code to position 2 in publish_array
        publish_array[3] = value1; // add value1 from Arduino code to position 3 in publish_array
        publish_array[4] = value2; // add value2 from Arduino code to position 4 in publish_array
        publish_array[5] = value3;

        sheet.appendRow(publish_array); // publish data in publish_array after the last row of data in the sheet

        str = "Success"; // string to return back to Arduino serial console
        SpreadsheetApp.flush();
        break;
    }

    return ContentService.createTextOutput(str);
  } // endif (parsedData !== undefined)
  else {
    return ContentService.createTextOutput(
      "Error! Request body empty or in incorrect format."
    );
  }
}