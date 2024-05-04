const http = require("http");
const fs = require("fs");
const path = require("path");
const querystring = require("querystring");
const port = 3000;
const addon = require("./index")

const handlers = {
    GET: {
        '/': (req, res) =>{
            fs.readFile(path.join(__dirname, 'index.html'), (err, data) =>{
                if(err){
                    res.writeHead(500);
                    res.end(err);
                    return;
                }
                res.writeHead(200, {'Content-Type': 'text/html'});
                res.end(data);
            });
        }
    },
    POST: {
        '/': (req,res) => {
        let body = '';
        req.on('data', chunk =>{
            body += chunk.toString();
        });
        req.on('end', () =>{
            const formData = querystring.parse(body);
            const textInput = formData.textInput;
            res.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
            res.end(addon.checkUser(textInput));
        });
        }
    }
}

const server = http.createServer((req, res) =>{

    const {method, url} = req;
    const handler = handlers[method] && handlers[method][url];

    if(handler){
        handler(req, res)
    } else {
        res.writeHead(404);
        res.end('Not Found')
    }
});
server.listen(port, () => {
    console.log(`Server running at http://localgost:${port}/`)
});