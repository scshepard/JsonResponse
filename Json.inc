<?php
error_reporting(E_ALL);
ini_set("display_errors", 1);
class Json
{
	// class Page's attributes
	public $content;
	public $mask;
	public $mysqli;
	public $programmask;

	public function setMysqli($mysqli) {
		$this->mysqli = $mysqli;
	}

	public function getMysqli() {
		return $this->mysqli;
	}

	// class Page's operations/methods
	public function __set($name, $value)
	{
		$this->name = $value;
	}

	public function setAuthorizedFunctionMask($mask) {
		//echo "setAuthorizedFunctionMask set to $mask<br />";
		$this->mask = $mask;
	}

	public function getAuthorizedFunctionMask() {
		//echo "getAuthroizedFunctionMask returning $this->mask<br />";
		return $this->mask;
	}

	public function setProgramMask($programmask) {
		// 3 Jan 2013
		//echo "setProgramMask set to $programmask<br />";
		$this->programmask = $programmask;
	}

	public function getProgramMask() {
		
		// 3 Jan 2013
		//echo "getProgramMask returning $this->programmask<br />";
		return $this->programmask;
	}

	/*
		Display the "program" specific query results
	*/

	public function DisplayCommunityHobbyManagement()
	// 3 Jan 2013
	{
		$self = $_SERVER["PHP_SELF"];
		$mysqli = $this->getMysqli();
		$programmask = "";

		?>
		<div id="reset">
		<h3><a onclick="resetQuery()">Reset Query</a></h3>
		</div>
		<?php
		echo "<div id=\"subWrapper\">";

	
		$delete = false;
		$insert = false;
		$edit = false;
		$view = false;
		
		if ($programmask == "delete") {
			$delete = true;
			$edit = true;
			$view = true;
		}
		
		if ($programmask == "modify") {
			$edit = true;
		}
		
		if ($programmask == "insert") {
			$insert = true;
		}
		
		if ($programmask == "view") {
			$view = true;
		}

		$name = "";
		$SessionName = "";
		if (isset($_SESSION["SessionName"])) {
			$SessionName = $_SESSION['SessionName'];
		}

		if (!empty($SessionName)) {
			;
			//echo "<h2>SessionName : $SessionName</h2>";
		} else {
			//$_SESSION["SessionName"] = "wee";
			;
		}

		$req = $_SERVER["REQUEST_METHOD"];

		echo "<p class=\"subheads\">";
		echo "<a onclick = \"displayQueryResults('ViewState','','','')\" >United States City Names</a>";
		echo "</p>";

		?>
		</div>
		<?php
	}

	public function DisplayPopups()
	// 3 Jan 2013
	{

		$self = $_SERVER["PHP_SELF"];
		echo '<div id="entrypopups">';
	}

	public function ConnectDatabase()
	// 3 Jan 2013
	{
		$mysqli = db_connect();
		if (mysqli_connect_errno()) {
			printf("Connect failed: %s\n", mysqli_connect_error());
			return false;
			exit();
		}
		//$d = "texty";
		//$this->Decode($d);
		$this->mysqli = $mysqli;
		$this->setMysqli($mysqli);
		return $mysqli;
	}

	public function DisplayServer()
	// 3 Jan 2013
	{
		$serve = $_SERVER["SERVER_NAME"];
		echo '<div id="server" class="server">';
		echo "Server : " .$serve;
		echo "</div>";
	}

	public function DisplayDatabase()
	// 3 Jan 2013
	{
		$mysqli = $this->getMysqli();
		echo '<div id="database" class = "database">';
		$get_gov_sql = "
		SELECT DATABASE()
		";
	
		$get_gov_res = mysqli_query($mysqli, $get_gov_sql) or die(mysqli_error($mysqli));
		$num_rows = mysqli_num_rows($get_gov_res);

		if ($num_rows > 0) {
			$gov_recs = mysqli_fetch_array($get_gov_res);
			$record = $gov_recs[0];
			$db = "LocoollyDatabase = '$record';";
			?>
			<script>
			<?php echo $db; ?>
			</script>
			<?php
			echo "Database : " . $record;
		}
		echo '</div>';
	}

	public function Decode($string)
	{
		$string = str_replace("%25","%",$string);
		$string = str_replace("%20"," ",$string);
		$string = str_replace("%23","#",$string);
		$string = str_replace("%26","&",$string);
		$string = str_replace("%27","'",$string);
		$string = str_replace("%29",")",$string);
		$string = str_replace("%2B","+",$string);
		$string = str_replace("+"," ",$string);
		$string = str_replace("%2C",",",$string);
		$string = str_replace("%2F","/",$string);
		$string = str_replace("+"," ",$string);
		$string = str_replace("%40","@",$string);
		$string = str_replace("%27","'",$string);

		return $string;
	}
	
	public function DisplayHeader($title)
	// 3 Jan 2013
	{
		?>
		<!DOCTYPE html>
		<html>
		<head>
		<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
		<meta name="author" content ="Steven C Shepard" />
		<meta name="description" content = "A template for Locoolly Production sites" />
		<meta name="keywords" content="web development, webdev, html5" />
		<meta name="robots" content="noindex" />
		<?php
		echo "<title>" .$title . "</title>";
		?>
		<link rel="shortcut icon" href="favicon.ico" />
		<script src="Template.js" type="text/javascript"></script>
		<link href="Template.css" rel="stylesheet" type="text/css" />
		</head>
		<header>
		<script>
		var Json = new Object();
		Json.mode = "Default";
		Json.CountyName = "";
		jsondata = "";
		jsonobject = "";

		function init() {
			;
		}
		function resetQuery() {
			Json.mode = "Default";
			displayQueryResults('Default','','','');
		}

		function removePopups() {
			var div = document.getElementById('subWrapper');
			
			if (div) {
				results = div.hasChildNodes();

				if (results) {
					while (div.hasChildNodes()) {
						//alert("removing Last Child");
						div.removeChild(div.lastChild);
					}
				}
			}
		}

		function dummy() {
			;
		}

		function displayQueryResults(mode, StateAbbreviation, CountyID, CityID) {
			var div = document.getElementById("submitSpecialForm");
			removePopups();
			
			/*
				Order of compare and reset VERY important!
			*/
			
			if (mode == 'Default') {
				//alert("default!");
				Json.mode = "Default";
				var home = document.getElementById("subWrapper");
				var div = document.createElement("a");
				div.className = "subheads";
				div.innerHTML = "<a " + "onclick = \"displayQueryResults('ViewState','', '', '')\">United States City Names</a>";
						
				home.appendChild(div);
				
				//echo "<a onclick = \"submitSpecialFormJS('ViewState','','','')\" >United States City Names</a>";
				//alert("Default!");
				return true;
				/*
					SELECT StateName, StateAbbreviation, StateID
					FROM State
					ORDER BY StateName
				*/
			}
			
			if (mode == 'ViewState') {
				Json.mode = "ViewState";
				/*
					SELECT StateName, StateAbbreviation, StateID
					FROM State
					ORDER BY StateName
				*/

				/*
					SELECT CountyName, CountyID, S.StateID
					FROM County
					INNER JOIN State S
					ON County.StateID = S.StateID
					WHERE S.StateAbbreviation = '".$State."'
					ORDER BY StateName
				*/
			}
			
			
			if (mode == 'ViewCounty') {
				//alert("ViewCounty!");
				Json.mode = "ViewCounty";

				/*
					SELECT CountyName, CountyID, S.StateAbbreviation
					FROM County
					INNER Join State S
					ON County.StateID = S.StateID
					WHERE StateAbbreviation = '".$StateAbbreviation."'
					ORDER BY CountyName
				*/

				/*
					SELECT CityName, CityID
					FROM City
					WHERE CountyID = '".$CountyID."'
					ORDER BY CityName
				*/
			}
			
			if (mode == 'ViewCity') {
				//alert("ViewCity!");
				Json.mode = "ViewCity";

				/*
					SELECT CityName, CityID
					FROM City
					WHERE CountyID = '".$CountyID."'
					ORDER BY CityName
				*/

				/*
					
				*/
			}

			//alert("mode : " + mode);
			//alert("StateAbbreviation : " + StateAbbreviation);
			//alert("CountyID : " + CountyID);

			req = new XMLHttpRequest();
			url = "queryDatabaseJson.php";
			url += "?mode="+mode;
			url += "&StateAbbreviation="+StateAbbreviation;
			url += "&CountyID="+CountyID;
			url += "&CityID="+CityID;
			url += "&sid="+Math.random();
			//console.log("query : " + url);
			
			req.open("GET",url, false);
			req.send(null);
			req.onreadystatechange = dummy;
			var text = req.responseText;
			//console.log("response text : " + text);

			jsonobject = JSON.parse(text);
			var length;
			
			length = jsonobject.resultSet.length;
			console.log("Length : " + length);
			var nbr = jsonobject.count;
			var error = jsonobject.error;
			var sql = jsonobject.sql;

			//console.log("nbr: : " + nbr);
			//console.log("error : " + error);
			//console.log("sql : " + sql);

			/*
				 To go the otherway around:
				 var myJSONText = JSON.stringify(myObject, replacer);
			*/

			var matrix;
			var name;
			var abbr;
			var id;
			var index = 1;
			var count = 0;
			var row = 0;

			var home = document.getElementById("subWrapper");
			if (!home) {
				alert("Can't find home!");
				return false;
			}

			if (mode == "ViewState") {
				var i;

				var div = document.createElement("div");
				div.id = "subWrapper0";
				home.appendChild(div);

					for (i = 0; i < nbr; i++ ) {
						var n = jsonobject.resultSet[i];
						count++;

						var classname = "statesCol" + index;
						var id = "states" + count;

						abbr = n.StateAbbreviation;
						name = n.StateName;
						id = n.StateID
						matrix = n.Count;

			
						//console.log("results " + abbr + " , " + name + " , " + id + " , " + matrix);
						//var el = document.createElement("div");
						var p = document.createElement("p");
						p.id = id;
						p.className = classname;
						p.name = id;
						//p.onclick = "displayQueryResults('ViewCounty',abbr, '', '')";
						p.value = name;
						p.innerHTML = "<a " + "onclick = \"displayQueryResults('ViewCounty','" + abbr + "', '', '')\">" + name + " <span class=\"foundInfo\">(" + matrix + ")" + "</span></a>";
						div.appendChild(p);
						
						if (count % 4 == 0) {
							//echo "</div>";
							//alert("dumping row");
							row++;
							div = document.createElement("div");
							div.id = "subWrapper" + row;
							div.name = "subWrapper" + row;
							home.appendChild(div);
							index = 0;
						}
						index++;
					}
				}
				
				if (mode == "ViewCounty") {
					var i;

					var n;
					var statename = jsonobject.statename;
					var h3 = document.createElement("h3");
					h3.className = "center";
					h3.innerHTML = "Counties for " + statename;
					//alert("statename : " + x);
					home.appendChild(h3);

					var div = document.createElement("div");
					div.id = "subWrapper0";
					home.appendChild(div);
	
					for (i = 0; i < nbr; i++ ) {
						n = jsonobject.resultSet[i];
						count++;
						var classname = "statesCol" + index;
						var id = "states" + count;

						name = n.CountyName;
						id = n.CountyID;
						matrix = n.Count;
	
						//console.log("results " + name + " , " + id + " , " + matrix);
						//var el = document.createElement("div");
						var p = document.createElement("p");
						p.id = id;
						p.className = classname;
						p.name = id;
						//p.onclick = "displayQueryResults('ViewCounty',abbr, '', '')";
						p.value = name;
						p.innerHTML = "<a " + "onclick = \"displayQueryResults('ViewCity','" + StateAbbreviation + "', '" + id + "', '')\">" + name + " <span class=\"foundInfo\">(" + matrix + ")" + "</span></a>";
						div.appendChild(p);
						
						if (count % 4 == 0) {
							//echo "</div>";
							//alert("dumping row");
							row++;
							div = document.createElement("div");
							div.id = "subWrapper" + row;
							div.name = "subWrapper" + row;
							home.appendChild(div);
							index = 0;
						}
						index++;
					}
				}
				
			if (mode == "ViewCity") {
					var i;
					//alert("nbr : " + nbr);
					var countyname = jsonobject.countyname;
					var stateabbreviation = jsonobject.stateabbreviation;
					//alert("CountyName : " + countyname);
					//echo "<h3>Cities for $StateAbbreviation, $CountyName County</h3>";

					var h3 = document.createElement("h3");
					h3.className = "center";
					//h3.innerHTML = "Cities for " + StateAbbreviation + ", " + CountyName + " County";
					h3.innerHTML = "Cities for " + stateabbreviation + " , " + countyname + " County";
					home.appendChild(h3);

					var div = document.createElement("div");
					div.id = "subWrapper0";
					home.appendChild(div);
	
					for (i = 0; i < nbr; i++ ) {
						count++;
						n = jsonobject.resultSet[i];
						var classname = "statesCol" + index;
						var id = "states" + count;
						var name = n.CityName;
	
						var p = document.createElement("p");
						p.id = id;
						p.className = classname;
						p.name = id;
						//p.onclick = "displayQueryResults('ViewCounty',abbr, '', '')";
						p.value = name;
						//p.innerHTML = "<a " + "onclick = \"displayQueryResults('ViewCity','" + StateAbbreviation + "', '', '')\">" + name + " <span class=\"foundInfo\">(" + matrix + ")" + "</span></a>";
						p.innerHTML = "<a " + "onclick = \"displayQueryResults('ViewCity','" + StateAbbreviation + "', '', '')\">" + name + "</a>";
						div.appendChild(p);
						
						if (count % 4 == 0) {
							//echo "</div>";
							//alert("dumping row");
							row++;
							div = document.createElement("div");
							div.id = "subWrapper" + row;
							div.name = "subWrapper" + row;
							home.appendChild(div);
							index = 0;
						}
						index++;
					}

				}
	


		}
		</script>
		</header>
		<nav>
		</nav>
		<section>
		<?php
	}
	
	public function DisplayBody($h1) {
		// 3 Jan 2013
		?>
		<body>
		<div id="wrapper">
		<?php
		echo "<h1>" . $h1 . "</h1>";
		?>
		<?php
	}
	
	public function DisplayTitle()
	{
		?>
		<?php
		;
	}
	
	public function queryBrowser() {
		// 3 Jan 2013
		$IEflag = 0;
		$IE9flag = 0;
		$IE8flag = 0;
		$IE7flag = 0;
		$FireFoxFlag = 0;
		$SafariFlag = 0;
		$OperaFlag = 0;
		$ChromeFlag = 0;

		$browser = strtolower($_SERVER['HTTP_USER_AGENT']); // what browser they use.
	
		if(preg_match("/msie 9/", $browser)) {
			//Internet Explorer
			$IEflag = 0;
			$IE9flag = 1;
			$IE8flag = 0;
			$IE7flag = 0;
			return "IE9flag";
			}
		if(preg_match("/msie 8/", $browser)) {
			//Internet Explorer
			$IEflag = 0;
			$IE9flag = 0;
			$IE8flag = 1;
			$IE7flag = 0;
			return "IE8flag";
			}
		if(preg_match("/msie 7/", $browser)) {
			//Internet Explorer
			$IEflag = 0;
			$IE9flag = 0;
			$IE8flag = 0;
			$IE7flag = 1;
			return "IE7flag";
			}
		if (preg_match("/firefox/", $browser)) {
			//Firefox
			$FireFoxFlag = 1;
			return "FireFoxFlag";
		}
		
		if (preg_match("/chrome/", $browser)) {
			//Safari
			$ChromeFlag = 1;
			return "ChromeFlag";
		} else if (preg_match("/safari/", $browser)) {
			//Chrome
			$SafariFlag = 1;
			return "SafariFlag";
		}
		
		if (preg_match("/opera/", $browser)) {
			//Opera
			$OperaFlag = 1;
			return "OperaFlag";
		}
	}

	public function DisplayStyles()
	// 3 Jan 2013
	{
		?>
		</section>
		<aside>
		</aside>
		<style>
		.center {
			text-align: center;
		}
		* {
			margin: 0px;
			padding: 0px;
		}
		body * {
			font-family: Verdana;
			font-size: 1em;
		}

		fieldset.optionGroup {
			background: pink;
		}

		fieldset.optionGroup label {
			display: inline;
			float: none;
			width: 40px;
		}

		fieldset.optionGroup input {
			display: inline;
			float: none;
			width: 20px;
		}

		#hobbyRadioFalse {
			margin-left: 230px;
		}

		#hobbyRadioTrue {
			margin-left: 260px;
		}


		.SelectOption {
			display: block;
			float: left;
			margin-left: 14em;
			margin-top: -1.0em;
			background-color: #211;
			color: white;
		}
		
		.navigation
			{
				float: left;
				width: 100%;
				background: #333;
			}
			
			.navigation ul
			{
				margin: 0;
				padding: 0;
			}
			
			.navigation ul li
			{
				list-style-type: none;
				display: inline;
			}
			
			.navigation li a
			{
				display: block;
				float: left;
				padding: 5px 10px;
				color: #fff;
				text-decoration: none;
				border-right: 1px solid #fff;
			}
			.navigation li
			{
				color: #fff;
				text-decoration: none;
				padding: 1em;
				border-right: 1px solid #fff;
			}
			
		.navigation li a:hover {
			background: white;
			color: gold;
		}

		.action {
			font-size: 2em;
			color: pink;
		}
		p {
			color: green;
		}
		.database {
			font-size: 120%;
			color: red;
		}
		.server {
			font-size: 120%;
			color: blue;
		}
		.entryDisplay {
			background-color: #555;
			width: 14em;
			font-size: 90%;
			text-align: center;
			color: white;
		}
		.entryError {
			background-color: #555;
			background-color: #123;
			width: 14em;
			font-size: 90%;
			text-align: center;
			color: pink;
		}
		.inputReadOnly {
			position: absolute;
			margin-left: 4.2em;
			background-color: #555;
			font-size: 90%;
			text-align: center;
			color: pink;
		}
		
		.inputSpecial {
			position: absolute;
			font-size: 90%;
			margin-left: 4.1em;
			background-color: #211;
			color: white;
		}
		.inputDisplay {
			position: absolute;
			font-size: 90%;
			margin-left: 2.9em;
			background-color: #211;
			color: white;
		}
		.imgHobbyShots {
			position: absolute;
			margin-top: 80px;
			margin-left: 150px;
		}
		.inputError {
			position: absolute;
			font-size: 90%;
			margin-left: 4.1em;
			background-color: #823;
			color: pink;
		}
		.JsonName {
			font-size: 2em;
			color: pink;
		}
		#JsonName {
			font: purple;
		}
		.action {
			font-size: 120%;
			color: red;
		}
		#gMaps {
			position: absolute;
			width: 200px;
			height: 200px;
			left: 800px;
			left: 740px;
			left: 780px;
			top: 50px;
			background-color: pink;
		}
		div .entry {
			width: 800px;
			height: 30px;
			margin: 0 auto;
			background-color: blue;
			color: purple;
		}
		div .view {
			position: relative;
			background-color: yellow;
			width: 25px;
			height: 25px;
		}
		div .edit {
			position: relative;
			background-color: #111;
			width: 25px;
			height: 25px;
		}
		div .modify {
			position: relative;
			background-color: #111;
			width: 25px;
			height: 25px;
		}
		.details {
			color: #fff;
			width: 200px;
		}
		h1 {
			font-size: 25px;
		}
		.urlOLD {
			text-decoration: none;
			list-style-type: disc;
		}
		.urlOLD a {
			text-decoration: none;
			list-style-type: disc;
		}
		.urlOLD a:link {
			color: gold;
		}
		.urlOLD a:visited {
			color: gold;
		}
		.urlOLD a:hover {
			color: #111;
			border: 1px solid red;
		}
		.urlOLD a:active {
			color: gold;
		}
		.navigation {
			float: left;;
			width: 100%;
			padding-top: 5px;
			padding-bottom: 5px;
			background: #333;
		}
		
		li {
			text-decoration: none;
			list-style-type: disc;
			
			font: #987;
		}
		footer {
			clear:both;
		}
		
		</style>
		<?php
	}
	
	public function DisplayFooter()
	// 3 Jan 2013
	{
		?>
		</div>
		<footer>
		<address>
		</address>
		</footer>
		<?php
	}
}
