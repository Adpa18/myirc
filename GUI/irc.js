const spawn = require('child_process').spawn;
const clientIRC = spawn('./client');

let config = {
    nickName : "",
    serverName : "",
    users: [],
    channels: [{
        name: "",
        nb_users: 0
    }]
};

let logDOM;
let inputDOM;
let channelsDOM;

window.onload = function () {
    logDOM = document.getElementById("log");
    inputDOM = document.getElementById("bottomBar");
    channelsDOM = document.getElementById("left");

    clientIRC.stdout.on('data', (data) => {
        parseData(data);
    logDOM.innerHTML = logDOM.innerHTML + data;
});

    inputDOM.addEventListener("keydown", function (event) {
        if (event.keyCode == 13) {
            sendCMD(inputDOM.value);
            console.log(inputDOM.value);
            inputDOM.value = "";
        }
    })
}

function sendCMD(cmd) {
    clientIRC.stdin.write(cmd);
}

function parseData(data) {
    data = String(data).split("\n");
    for (let i = 0; i < data.length; ++i) {
        // console.log("line =>", data[i]);
        if (!data[i])
            continue;
        let keycode = data[i].match(/.* (\d{3}) .*/);
        if (!keycode)
            continue;
        switch (parseInt(keycode[1])) {
            case 001:
                init(data[i].match(/:(.*) 001 (.*) :/));
                break;
            case 392:
                config.users = [];
                break;
            case 393:
                getUser(data[i].match(/.*393.*:(.*)/));
                break;
            case 321:
                config.channels = [];
                channelsDOM.innerHTML = "";
                break;
            case 322:
                getChannel(data[i].match(/.*322.*?:(.*) (\d)/));
                break;
        }
    }
    console.log(config);
}

function init(data) {
    config.serverName = data[1];
    config.nickName = data[2];
    sendCMD("/USERS");
    sendCMD("/LIST");
}

function getUser(data) {
    if (data) {
        config.users.push(data[1]);
    }
}

function getChannel(data) {
    if (data) {
        config.channels.push({
            name : data[1],
            nb_users: data[2]
        });
        channelsDOM.innerHTML = channelsDOM.innerHTML
            + "<div class=\"channel\">"
            + data[1]
            + "<span class=\"nb_channel\">" + data[2] + "</span>"
            + "</div>";
    }
}