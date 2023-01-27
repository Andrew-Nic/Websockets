using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WebSocketSharp;
using WebSocketSharp.Server;

namespace csharp_server
{
    public class Echo: WebSocketBehavior
    {
        protected override void OnMessage(MessageEventArgs e)
        {
            Console.WriteLine("recibi informacion del cliente: " + e.Data);
            Send(e.Data);
        }
    }

    public class EchoAll: WebSocketBehavior
    {
        protected override void OnMessage(MessageEventArgs e)
        {
            Console.WriteLine("Mensaje Recibido del cliente para EchoAll: " + e.Data);
            Sessions.Broadcast(e.Data);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            string wsocketAddres = "ws://192.168.1.67:80";

            WebSocketServer wssv = new WebSocketServer(wsocketAddres);

            wssv.AddWebSocketService<Echo>("/Echo");
            wssv.AddWebSocketService<EchoAll>("/EchoAll");

            wssv.Start();
            
            Console.WriteLine("WS server started on " + wsocketAddres+"/Echo");
            Console.WriteLine("WS server started on " + wsocketAddres + "/EchoAll");

            Console.ReadKey();
            wssv.Stop();
        }
    }
}
