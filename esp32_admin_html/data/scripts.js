$(function() {
    // Side Bar Toggle
    $('.hide-sidebar').click(function() {
        $('#sidebar').hide('fast', function() {
            $('#content').removeClass('span9');
            $('#content').addClass('span12');
            $('.hide-sidebar').hide();
            $('.show-sidebar').show();
        });
    });

    $('.show-sidebar').click(function() {
        $('#content').removeClass('span12');
        $('#content').addClass('span9');
        $('.show-sidebar').hide();
        $('.hide-sidebar').show();
        $('#sidebar').show('fast');
    });
});

//WebSocket Conexión
var connection = new WebSocket('ws://' + location.hostname + '/ws', ['arduino']);

//Abrir el WebSocket
connection.onopen = function() {
    console.log('WS/ Connectado');
};

//Error
connection.onerror = function(error) {
    console.log('WS/ Error ', error);
};

//Cuando llega Mensaje llamamos la Función ProcessData
connection.onmessage = function(e) {
    console.log('Server: ', e.data);
    processData(e.data);
};

//Cerrar el Websocket
connection.onclose = function() {
    console.log('WS/ Cerrado');
};
//Camturar el Pathname del URL
let pathname = window.location.pathname;

function processData(data) {

    //Convertir la Dara en Json
    let json = JSON.parse(data);

    //Si estamos en el dashboard actualizamos los valores
    if (pathname == "/") {

        if (json.WFEstatus != null) {

            let WFEstatus = document.getElementById('WFEstatus');
            let MQTTStatus = document.getElementById('MQTTStatus');
            let MQTTBroker = document.getElementById('MQTTBroker');
            let WFDBM = document.getElementById('WFDBM');
            let WFPRC = document.getElementById('WFPRC');
            let WiFiChart = document.getElementById('WiFiChart');
            let PMEMChart = document.getElementById('PMEMChart');
            let ramChart = document.getElementById('ramChart');
            let cpuChart = document.getElementById('cpuChart');

            WFEstatus.innerHTML = json.WFEstatus;
            MQTTStatus.innerHTML = json.MQTTStatus;
            MQTTBroker.innerHTML = json.MQTTBroker;
            WFDBM.innerHTML = json.WFDBM + " dBm";
            WFPRC.innerHTML = json.WFPRC + " %";
            WiFiChart.innerHTML = json.WFPRC + " %";
            PMEMChart.innerHTML = json.PMEM + " %";
            ramChart.innerHTML = json.ram + " %";
            cpuChart.innerHTML = json.cpu + " °C";

            $(function() {
                var chart = window.chart = $('#chartWiFi').data('easyPieChart');
                chart.update(json.WFPRC);
                var chart = window.chart = $('#chartPMEM').data('easyPieChart');
                chart.update(json.PMEM);
                var chart = window.chart = $('#chartram').data('easyPieChart');
                chart.update(json.ram);
                var chart = window.chart = $('#chartcpu').data('easyPieChart');
                chart.update(json.cpu);
            });

        }
    }

}