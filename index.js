const addon = require("./build/Release/addon")

function checkUser(username){
    return addon.isUserAdmin(username)
}

module.exports = {checkUser}