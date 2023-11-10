using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HolePunching
{
    public class MessagingConsole
    {
        List<Message> history = new List<Message>();
        public event Action<string> onMessageSent;
        private string input = "";

        public MessagingConsole()
        {
        }

        public void Update()
        {
            if (Console.KeyAvailable)
            {
                ConsoleKeyInfo key = Console.ReadKey();

                if (key.Key == ConsoleKey.Enter && !string.IsNullOrEmpty(input))
                {
                    Send();
                }
                else if (key.Key == ConsoleKey.Backspace)
                {
                    input = input.Substring(0, input.Length - 1);
                }
                else
                {
                    input += key.KeyChar;
                }
            }
        }

        public void ReceiveMessage(Message message)
        {
            history.Add(message);
            Redraw();
        }

        public void Send()
        {
            history.Add(new Message("local", input));
            onMessageSent?.Invoke(input);
            input = "";
            Redraw();
        }

        private void Redraw()
        {
            Console.Clear();

            Console.WriteLine(input);
            Console.WriteLine("--- Messages ---");

            foreach (Message message in history)
            {
                Console.WriteLine(message);
            }

            Console.SetCursorPosition(input.Length, 0);
        }
    }
}
