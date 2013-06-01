<?php
require_once('db_fns.php');
error_reporting(E_ALL);
ini_set("display_errors", 1);

	//$x = db_connect();
	
	$type = "Undefined";

	class ResultSet {
		var $sql;
		var $count;
		var $error;
		var $resultSet = array();
		var $origin;
		var $server;
		var $database;
		var $stateabbreviation;
		var $statename;
		var $countyname;
		
		function set_database($database) {
			$this->database = $database;
		}

		function get_database() {
			return $this->database;
		}

		function set_server($server) {
			$this->server = $server;
		}

		function get_server() {
			return $this->server;
		}

		function set_countyname($countyname) {
			$this->countyname = $countyname;
		}
		
		function get_countyname() {
			return $this->countyname;
		}
		
		function set_stateabbreviation($stateabbreviation) {
			$this->stateabbreviation = $stateabbreviation;
		}
		
		function set_statename($statename) {
			$this->statename = $statename;
		}
		
		function get_statename() {
			return $this->statename;
		}
		
		function get_stateabbreviation() {
			return $this->stateabbreviation;
		}
		function set_origin($origin) {
			$this->origin = $origin;
		}

		function get_origin() {
			return $this->origin;
		}

		function set_error($error) {
			$this->error = $error;
		}

		function get_error() {
			return $this->error;
		}

		function set_count($count) {
			$this->count = $count;
		}

		function get_count() {
			return $this->count;
		}

		function set_sql($sql) {
			$this->sql = $sql;
		}

		function get_sql() {
			return $this->sql;
		}

		function set_results($initial) {
			$this->resultSet[] = $initial;
		}

		function add_results($resultSet) {
			$this->resultSet[] = $resultSet;
		}

		function get_results() {
			return $this->results;
		}
	}

	$city = new ResultSet();

	$mode = "";
	$StateAbbreviation = "";
	$CountyID = 0;
	$CityID = 0;

	if (isset($_GET['mode'])) {
		$mode = trim($_GET['mode']);
	}
	
	if (isset($_GET['StateAbbreviation'])) {
		$StateAbbreviation = $_GET['StateAbbreviation'];
		//echo "StateAbbreviation : $StateAbbreviation";
	}
	
	if (isset($_GET['CountyID'])) {
		$CountyID = $_GET['CountyID'];
	}
	
	if (isset($_GET['CityID'])) {
		$CityID = $_GET['CityID'];
	}

	$self = $_SERVER["PHP_SELF"];
	$serve = $_SERVER["SERVER_NAME"];

	$cmd = "LocoollySelf = '$self';";
	$server = "LocoollyServer = '$serve';";

	//connect to database
	$mysqli = db_connect();

	$get_gov_sql = "
		SELECT DATABASE()
	";

	$get_gov_res = mysqli_query($mysqli, $get_gov_sql) or die(mysqli_error($mysqli));
	$num_rows = mysqli_num_rows($get_gov_res);

	$database = "unk";
	if ($num_rows > 0) {
		$gov_recs = mysqli_fetch_array($get_gov_res);
		$database = $gov_recs[0];
		}

	//header('Content-type: application/json');
	$temp = array(); 

	if ($mode == "ViewState") {
		$get_gov_sql = "
			SELECT StateName, StateAbbreviation, StateID
			FROM State
			ORDER BY StateName
		";

		$get_gov_res = mysqli_query($mysqli, $get_gov_sql) or die(mysqli_error($mysqli));
		$num_rows = mysqli_num_rows($get_gov_res);
	
		$city->set_count($num_rows);
		$city->set_error(0);
		$city->get_count();
		$city->set_origin($self);
		$city->set_server($serve);
		$city->set_database($database);
		$city->set_sql($get_gov_sql);
		$city->get_sql();
	
		while($rec = mysqli_fetch_assoc($get_gov_res)) {
				$StateName = $rec['StateName'];
				$StateAbbreviation = $rec['StateAbbreviation'];
				$StateID = $rec['StateID'];

				$sql = "
					SELECT COUNT(CountyName) AS Count
					FROM County
					WHERE StateID = ".$StateID."
				";
				$get = mysqli_query($mysqli, $sql) or die(mysqli_error($mysqli));
				$res = mysqli_fetch_array($get);
				$Count = $res['Count'];

				$temp['Count'] = $Count;
				$rec = array_merge($rec,$temp);
				$city->add_results($rec);
		}
	}

	if ($mode == "ViewCounty") {
		$get_postal_sql = "
				SELECT StateAbbreviation, StateName
				FROM State
				WHERE StateAbbreviation = '".$StateAbbreviation."'
			";

		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$rec = mysqli_fetch_array($get_postal_res);
		$StateName = $rec['StateName'];
		//echo "StateName $StateName";
		$get_postal_sql = "
				SELECT CountyName, CountyID
				FROM County
				INNER Join State S
				ON County.StateID = S.StateID
				WHERE StateAbbreviation = '".$StateAbbreviation."'
				ORDER BY CountyName
			";

		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$postal_rows = mysqli_num_rows($get_postal_res);

		$city->set_count($postal_rows);
		$city->set_error(0);
		$city->get_count();
		$city->set_origin($self);
		$city->set_server($serve);
		$city->set_database($database);
		$city->set_sql($get_postal_sql);
		$city->get_sql();
		$city->set_stateabbreviation($StateAbbreviation);
		$city->set_statename($StateName);

		$temp = array();

		while ($rec = mysqli_fetch_array($get_postal_res)){
			$CountyName = $rec['CountyName'];
			$CountyID = $rec['CountyID'];
			$sql = "
				SELECT COUNT(CityName) AS Count
				FROM City
				WHERE CountyID = '".$CountyID."'
			";

			$get = mysqli_query($mysqli, $sql) or die(mysqli_error($mysqli));
			$res = mysqli_fetch_array($get);
			$Count = $res['Count'];

			$temp['Count'] = $Count;
			$rec = array_merge($rec,$temp);
			$city->add_results($rec);
			}
	}

	if ($mode == "ViewCity") {
		$get_postal_sql = "
				SELECT StateAbbreviation, StateName
				FROM State
				WHERE StateAbbreviation = '".$StateAbbreviation."'
			";
	
		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$postal_rows = mysqli_num_rows($get_postal_res);
		$rec = mysqli_fetch_array($get_postal_res);
		$StateName = $rec['StateName'];
		$city->set_stateabbreviation($StateAbbreviation);
		$city->set_statename($StateName);

		$get_postal_sql = "
				SELECT CountyName
				FROM County
				WHERE CountyID = '".$CountyID."'
			";
	
		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$postal_rows = mysqli_num_rows($get_postal_res);
		$rec = mysqli_fetch_array($get_postal_res);
		$CountyName = $rec['CountyName'];
		
		$get_postal_sql = "
				SELECT CityName, CityID
				FROM City
				WHERE CountyID = '".$CountyID."'
				ORDER BY CityName
			";
	
		$get_postal_res = mysqli_query($mysqli, $get_postal_sql) or die(mysqli_error($mysqli));
		$postal_rows = mysqli_num_rows($get_postal_res);
		
		$city->set_count($postal_rows);
		$city->set_error(0);
		$city->get_count();
		$city->set_origin($self);
		$city->set_server($serve);
		$city->set_database($database);
		$city->set_sql($get_postal_sql);
		$city->set_countyname($CountyName);
		$city->set_stateabbreviation($StateAbbreviation);
		$city->set_statename($StateName);
		$city->get_sql();
		$temp = array();

		while ($rec = mysqli_fetch_array($get_postal_res)){
			$CityName = $rec['CityName'];
			$CityID = $rec['CityID'];
			$sql = "
				SELECT COUNT(PostalCode) AS Count
				FROM PostalCode
				WHERE CityID = '".$CityID."'
			";

			$city->add_results($rec);
			}
	}

	$data = json_encode($city);
	echo $data;
