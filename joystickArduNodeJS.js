//!Launch MAME with -keyboardprovider dinput

var SerialPort = require("serialport");
var robot = require("robotjs");
var arduPort;
var port;
var controls = {x:{0:'left',1:'',2:'right'},y:{0:'down',1:'',2:'up'}}
var joystick = {x:1,y:1,a:0,b:0,c:0,d:0,e:0,f:0}

function findConnection() {
    console.log("Searching for arduino");
    arduPort = "";
    //while(arduPort=="") {
        SerialPort.list(function(err,ports) {
            ports.forEach(function(port) {
                console.log("Puerto: "+port.comName);
                console.log("Dispositivo: "+port.manufacturer);
                if(port.manufacturer.indexOf("Arduino")>-1) {
                    arduPort = port.comName;
                    start();
                }
            });
        });
    //}
}

function start() {
    port = new SerialPort(arduPort,
    {baudRate: 9600,
    parser: SerialPort.parsers.readline("!")});

    port.on('open',function() {
        console.log("Port opened");
    })
    port.on('data',connector);
    port.on('disconnect',function(){console.log("ERROR: Disconnection");port.removeListener('data',handle);joystick = {x:1,y:1};handle("[1;1]");findConnection()});
}

function connector(data) {
    console.log("Ardu said: "+data);
    if(data.indexOf("PROYECT_JOY")>-1) {
        console.log("Starting");
        port.write("OK");
        port.drain();
        port.flush();
        port.removeListener('data',connector);
        port.on('data',handle)
    }
}

function handle(data) {
    joystick.x = data[1];
    joystick.y = data[3];
    for(var i=0;i<=2;i++) {
        if(i==1)continue;
        if(joystick.x!=i)
            robot.keyToggle(controls.x[i],'up');
        if(joystick.y!=i)
            robot.keyToggle(controls.y[i],'up');
    }
    console.log("["+joystick.x+";"+joystick.y+"]");
}

setInterval(function() {
    if(joystick.x!="1") {
        robot.keyToggle(controls.x[joystick.x],'down');
    }
    if(joystick.y!="1") {
        robot.keyToggle(controls.y[joystick.y],'down');
    }
},100)

findConnection();
//console.log();