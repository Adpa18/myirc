const spawn = require('child_process').spawn;
const clientIRC = spawn('./client');

let config = {
    nickName : "",
    serverName : "",
    users: [],
    channels: [],
    channels_msg: [{
        author: "",
        msg: ""
    }]
};

let logDOM;
let inputDOM;
let channelsDOM;

window.onunload = function () {
    clientIRC.kill();
}

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
    console.log("Sending => " + cmd);
    clientIRC.stdin.write(cmd);
}

function parseData(data) {
    data = String(data).split("\n");
    for (let i = 0; i < data.length; ++i) {
        // console.log("line =>", data[i]);
        if (!data[i])
            continue;
        if (!checkKeyCode(data[i])) {
            checkCMD(data[i]);
        }
    }
    console.log(config);
}

function checkKeyCode(data) {
    let keycode = data.match(/.* (\d{3}) .*/);
    if (!keycode || !keycode[1])
        return (false);
    switch (parseInt(keycode[1])) {
        case 001:
            init(data.match(/:(.*) 001 (.*) :/));
            break;
        case 392:
            config.users = [];
            break;
        case 393:
            getUser(data.match(/.*393.*:(.*)/));
            break;
        case 321:
            config.channels = [];
            channelsDOM.innerHTML = "";
            break;
        case 322:
            let channel = data.match(/.*322.*?:(.*) (\d)/);
            addChannel(channel[1], channel[2]);
            break;
    }
    return (true);
}

function checkCMD(data) {
    let cmd = data.match(/.* (.*) :.*/);
    if (!cmd || !cmd[1])
        return (false);
    switch (cmd[1]) {
        case "JOIN":
            joinChannel(data.match(/:(.*)!.* :(.*)/));
            break;
    }
    return (true);
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

function joinCMD(name) {
    sendCMD("/JOIN " + name);
}

function joinChannel(data) {
    // let join = data.match(/:(.*)!.* :(.*)/);
    // if (join[1] == config.nickName)
    //     addChannel(join[2], 1);
    sendCMD("/LIST");
}

function addChannel(name, nb) {
    if (name && !config.channels[name]) {
        if (!nb)
            nb = 1;
        config.channels[name] = nb;
        channelsDOM.innerHTML = channelsDOM.innerHTML
            + "<div class=\"channel\" onclick=\'joinCMD(\""+name+"\");\'>"
            + name
            + "<span class=\"nb_channel\">" + nb + "</span>"
            + "</div>";
    }
}