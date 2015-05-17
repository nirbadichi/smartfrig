using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common
{
    public class StorageItem 
    {
        public string id { get; set; }
        public string name { get; set; }
        public string type { get; set; }
        public int quantity { get; set; }
        public string image_id { get; set; }
    }
}
