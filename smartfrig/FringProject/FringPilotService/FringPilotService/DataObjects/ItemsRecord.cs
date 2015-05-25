using Microsoft.WindowsAzure.Mobile.Service;
using System;
using Newtonsoft.Json;

namespace FringPilotService.DataObjects
{
    public class ItemsRecord : EntityData
    {
        [JsonProperty(PropertyName = "name")]
        public string Name { get; set; }

        [JsonProperty(PropertyName = "quantity")]
        public bool Quantity { get; set; }

        [JsonProperty(PropertyName = "class")]
        public string Class { get; set; }

        [JsonProperty(PropertyName = "price")]
        public float Price { get; set; }

        [JsonProperty(PropertyName = "date")]
        public string Date { get; set; }

        [JsonProperty(PropertyName = "imageId")]
        public string ImageId { get; set; }
    }
}