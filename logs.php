<?php
$file = file_get_contents(__DIR__ . "/logs.json");
$loads = json_decode($file, true);
?>
<!DOCTYPE html>
<html>

<head>
    <!--Import Google Icon Font-->
    <link href="static/css/material-icons.css" rel="stylesheet">
    <!--Import materialize.css-->
    <link type="text/css" rel="stylesheet" href="static/css/materialize.min.css" media="screen,projection" />

    <!--Let browser know website is optimized for mobile-->
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />

    <title>Sequential Load</title>

    <style>
        body {
            font-size: 1.1rem;
        }
    </style>
</head>

<body>
    <section class="section container">
        <h1>Sequential Load Logs</h1>
    </section>
    <section class="section container">
        <div class="card grey lighten-5">
            <div class="card-content">
                <table class="highlight">
                    <thead>
                        <tr>
                            <th>#</th>
                            <th>Device</th>
                            <th>IP</th>
                            <th>Time</th>
                            <th>Temperature</th>
                            <th>Load</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
						$i = 1;
						foreach ($loads as $load) {
							if (isset($load["data"]["user"]) && isset($load["ip"]) && isset($load["time"]) && isset($load["data"]["temperature"]) && isset($load["data"]["load"])) {
								?>
                        <tr>
                            <td><?= $i ?></td>
                            <td><?= $load["data"]["user"] ?></td>
                            <td><?= $load["ip"] ?></td>
                            <td class="is-time"><?= $load["time"] ?></td>
                            <td><?= $load["data"]["temperature"] ?> &deg;C</td>
                            <td><?= $load["data"]["load"] ?></td>
                        </tr>
                        <?php
						$i++;
					}
				}
				?>
                    </tbody>
                </table>
            </div>
        </div>
    </section>
    <script type="text/javascript" src="static/js/jquery-3.3.1.min.js"></script>
    <script type="text/javascript" src="static/js/moment.js"></script>
    <script type="text/javascript" src="static/js/materialize.min.js"></script>
    <script>
        $('.is-time').each(function() {
            const time = $(this).html();
            $(this).html(moment.unix(time).format('llll'));
        });
    </script>
</body>

</html> 