using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HolePunching
{
    public struct Message
    {
        public string sender;
        public string message;

        public Message(string sender, string message)
        {
            this.sender = sender;
            this.message = message;
        }

        public override string ToString()
        {
            return String.Format("[{0}] {1}", sender, message);
        }
    }
}
