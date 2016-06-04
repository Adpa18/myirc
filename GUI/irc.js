const spawn = require('child_process').spawn;
const clientIRC = spawn('../client');

let config = {
    nickName : "",
    serverName : "",
    currentChannel: "",
    users: [],
    channels: [],
    msgs: [[{
        author: "",
        msg: ""
    }]]
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
    msgsDOM = document.getElementById("msgs");

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
    if (cmd[0] != "/" && config.currentChannel) {
        appendMsg(config.currentChannel, config.nickName, cmd);
        cmd = "/MSG " + config.currentChannel + " " + cmd;
    }
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
            initLeft();
            break;
        case 322:
            let channel = data.match(/.*322.*?:(.*) (\d)/);
            addChannel(channel[1], channel[2]);
            break;
    }
    return (true);
}

function checkCMD(data) {
    let cmd = data.match(/ ([^ ]+) /);
    if (!cmd || !cmd[1])
        return (false);
    switch (cmd[1]) {
        case "JOIN":
            joinChannel(data.match(/:(.*)!.* :(.*)/));
            break;
        case "PRIVMSG":
            recvMsg(data.match(/:(.*)!~.* [^ ]+ (.*) :(.*)/));
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
    if (name[0] == "#")
        sendCMD("/JOIN " + name);
    msgsDOM.innerHTML = "";
    config.currentChannel = name;
    if (!config.msgs[name])
        return;
    for (let i = 0; i < config.msgs[name].length; ++i) {
        printMsg(config.msgs[name][i].author, config.msgs[name][i].msg);
    }
}

function joinChannel(data) {
    if (data[1] == config.nickName && data[2])
        config.currentChannel = data[2];
    sendCMD("/LIST");
}

function recvMsg(data) {
    console.log(data);
    if (!data || !data[1] || !data[2] || !data[3])
        return;
    appendMsg(data[2], data[1], data[3]);
}

function appendMsg(name, author, msg) {
    if (!name || !author || !msg)
        return;
    if (!config.msgs[name])
        config.msgs[name] = [];
    config.msgs[name].push({author: author, msg: msg});
    if (name != config.currentChannel)
        return;
    printMsg(author, msg);
}

function printMsg(author, msg) {
    msgsDOM.innerHTML = msgsDOM.innerHTML
        + "<p class='msg'>"
        + "<span class='author'>" + author + "</span>"
        + msg
        + "</p>";
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

function initLeft() {
    config.channels = [];
    channelsDOM.innerHTML = "";
    for (let i = 0; i < config.users.length; ++i) {
        if (config.users[i] == config.nickName)
            continue;
        channelsDOM.innerHTML = channelsDOM.innerHTML
            + "<div class=\"channel_user\" onclick=\'joinCMD(\""+config.users[i]+"\");\'>"
            + config.users[i]
            + "</div>";
    }
}