using Microsoft.WindowsAzure.Mobile.Service;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace FringProjectMobileService.DataObjects
{
    public class StorageItem : EntityData
    {
        public string Id { get; set; }

        [JsonProperty(PropertyName = "name")]
        public string Name { get; set; }
        [JsonProperty(PropertyName = "type")]
        public string Type { get; set; }
        [JsonProperty(PropertyName = "quantity")]
        public int Quantity { get; set; }
        [JsonProperty(PropertyName = "image_id")]
        public string Image_id { get; set; }
    }
}