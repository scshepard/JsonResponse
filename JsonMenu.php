<?php
session_start();
error_reporting(E_ALL);
ini_set("display_errors", 1);

$_SESSION['ref'] = "JsonMenu.php";
require_once('Json.inc');
require_once('db_fns.php');

$Json = new Json();

$IEflag = 0;
$FireFoxFlag = 0;
$SafariFlag = 0;
$OperaFlag = 0;
$ChromeFlag = 0;
$Json->queryBrowser();

$title = "Community Management Menu";
$header = "Locoolly Data Entry";
$Json->DisplayHeader($header);
$Json->DisplayStyles();
$Json->DisplayBody($title);

?>
<?php

$mysqli = $Json->ConnectDatabase();
echo "mysqli : $mysqli";
if ($mysqli == "") {
	echo "Open failed!<br >";
	echo "<a href='http://www.locoolly.com/JsonResponse/Response.json'>Example of Json Response</a>";
	exit;
}
$Json->DisplayDatabase();
$Json->DisplayServer();
$Json->DisplayPopups();

/*
	Create the "program" specific sql query
*/

/*
	Display the "program" specific query results
*/

$Json->DisplayCommunityHobbyManagement();

$Json->DisplayFooter();

$Json->setProgramMask('$ProgramMask');
$Json->getProgramMask();
?>
<script type="text/javascript">
window.onload = init;
</script>
</body>
</html>