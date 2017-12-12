const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
  input: fs.createReadStream('../tree_tests/tree_1000000.txt'),
});
var wstream = fs.createWriteStream('../tree_tests/tree_answer_1000000.txt');
var num_nodes;
var commands = [];

rl.on('line', (line) => {
    if(line === '') {
        // Do nothing
    }
    else {
        nodes = line.split(' ');
        if(nodes.length === 1) {
            console.log(parseInt(nodes[0]));
            num_nodes = parseInt(nodes[0]);
        }
        else {
            if(nodes[1] > nodes[2])
                [nodes[1], nodes[2]] = [nodes[2], nodes[1]];
            if(line.startsWith('add')) {
                commands.push([0, parseInt(nodes[1]), parseInt(nodes[2])]);
            }
            else if(line.startsWith('rem')) {
                commands.push([1, parseInt(nodes[1]), parseInt(nodes[2])]);
            }
            else if(line.startsWith('conn')) {
                commands.push([2, parseInt(nodes[1]), parseInt(nodes[2])]);
            }
        }
    }
});

rl.on('close', () => {
    // Now, do the testing
    var results = [];
    var starttime = process.hrtime();
    var createVertex = require('dynamic-forest');
    var nodes = [];
    var edges = {};
    for(var i = 0; i < num_nodes; i++) {
        nodes.push(createVertex(i));
    }
    for(var i = 0; i < commands.length; i++) {
        var command = commands[i];
        if(command[0] === 0) {
            edges[num_nodes * command[1] + command[2]] = nodes[command[1]].link(nodes[command[2]]);
        } else if (command[0] === 1) {
            edges[num_nodes * command[1] + command[2]].cut();
        } else if (command[0] === 2) {
            var check = nodes[command[1]].connected(nodes[command[2]]);
            results.push(check);
        }
    }

    var endtime = process.hrtime();
    console.log(starttime, endtime);
    for(res in results) {
        if(res === true) {
            wstream.write('YES\n');
        } else {
            wstream.write('NO\n');
        }
    }
    wstream.end();
});
