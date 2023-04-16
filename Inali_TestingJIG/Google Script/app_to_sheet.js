function doGet(e) {
  return Authentication(e);
}
function doPost(e) {
  return Authentication(e);
}
function Authentication(e) {
  if (e.parameter.func == "Create") {
    var ss = SpreadsheetApp.openById(e.parameter.ID);
    var sh = ss.getSheetByName(e.parameter.SH);

    var rg = sh.getName() + "!" + sh.getDataRange().getA1Notation();
    var email = e.parameter.email;
    var sql = "\"Select B where B='" + email + "'\"";
    var qry = "=IFERROR(query(" + rg + "," + sql + '),"")';

    var ts = ss.insertSheet();

    var setQuery = ts.getRange(1, 1).setFormula(qry);
    var getResult = ts.getDataRange().getValues();
    ss.deleteSheet(ts);
    if (getResult == "") {
      var data = [
        e.parameter.fullname,
        e.parameter.email,
        e.parameter.password,
        e.parameter.batch_no,
      ];
      sh.appendRow(data);
      return ContentService.createTextOutput(getResult);
    }
  }
  ////////////////////////////////////////////////////////////////
  if (e.parameter.func == "Login") {
    var ss = SpreadsheetApp.openById(e.parameter.ID);
    var sh = ss.getSheetByName(e.parameter.SH);

    var email = e.parameter.email;
    var password = e.parameter.password;

    var rg = sh.getName() + "!" + sh.getDataRange().getA1Notation();
    var sql = "\"Select A,B,C where B='" + email + "'\"";
    var qry = "=IFERROR(query(" + rg + "," + sql + '),"")';

    var ts = ss.insertSheet();
    var setQuery = ts.getRange(1, 1).setFormula(qry);
    var getResult = ts.getDataRange().getValues();

    var getPWD = ts.getRange(1, 3).setValues();
    var getFullName = ts.getDataRange(1, 1).getValues();
    ss.deleteSheet(ts);

    if (getResult != "") {
      if (getPWD == password) {
        return ContentService.createTextOutput(getFullName);
      } else {
        return ContentService.createTextOutput("ERPWD");
      }
    } else {
      return ContentService.createTextOutput(getResult);
    }
  }

  //////////////////////////////////////////////
  if (e.parameter.func == "SendEmail") {
    var ss = SpreadsheetApp.openById(e.parameter.ID);
    var sh = ss.getSheetByName(e.parameter.SH);

    var email = e.parameter.email;

    var rg = sh.getName() + "!" + sh.getDataRange().getA1Notation();
    var sql = "\"Select A,B,C where B='" + email + "'\"";
    var qry = "=IFERROR(query(" + rg + "," + sql + '),"")';

    var ts = ss.insertSheet();
    var setQuery = ts.getRange(1, 1).setFormula(qry);
    var getResult = ts.getDataRange().getValues();
    var getPWD = ts.getRange(1, 3).setValues();
    ss.deleteSheet(ts);

    if (getResult != "") {
      GmailApp.sendEmail(
        "" + email + "",
        "here is your password",
        "" + getPWD + ""
      );
    } else {
      return ContentService.createTextOutput(getResult);
    }
  }
}
