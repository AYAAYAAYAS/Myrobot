function WsInit(){}
var ws = new WebSocket("ws://"+window.location.hostname+":9988");
function WebSocketTest()
{
            if ("WebSocket" in window)
            {
               // alert("您的浏览器支持 WebSocket!");
               
               // 打开一个 web socket

               ws.onopen = function()
               {
                  // Web Socket 已连接上，使用 send() 方法发送数据
                  ws.send("发送数据");
                  alert("连接成功");
               };
                
               ws.onmessage = function (evt) 
               { 
                  var received_msg = evt.data;
                  console.log(received_msg);
               };
                
               ws.onclose = function()
               { 
                  // 关闭 websocket
                  //alert("连接已关闭..."); 
               };
            }
            
            else
            {
               // 浏览器不支持 WebSocket
               //alert("您的浏览器不支持 WebSocket!");
            }
}
