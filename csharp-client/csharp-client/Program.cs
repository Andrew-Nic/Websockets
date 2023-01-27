using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

using WebSocketSharp;
using Newtonsoft.Json;

namespace csharp_client
{
    internal class Program
    {

        static void Main(string[] args)
        {

            string socketAddres = "ws://192.168.1.67:80/EchoAll";

            // create an instance of websocket client that will be properly disposed
            using (WebSocket ws = new WebSocket(socketAddres)) 
            {
                ws.OnMessage += Ws_OnMessage;
                ws.Connect();
                if (ws.ReadyState == WebSocketState.Open)
                {
                    ws.Send("hola server!");
                }
                else
                {
                    Console.WriteLine("Error: la conexión no está abierta.");
                }

                //ws.Send("hola server!");

                Console.ReadKey();
            }
              
        }

        private static void Ws_OnMessage(object sender, MessageEventArgs e)
        {
            Console.WriteLine("recibido del servidor: " + e.Data );

        }
    }
}
