using Microsoft.WindowsAzure.Mobile.Service;
using System;
using Newtonsoft.Json;

namespace FringPilotService.DataObjects
{
    public class RecipeRecord : EntityData
    {
        [JsonProperty(PropertyName = "name")]
        public string Name { get; set; }

        [JsonProperty(PropertyName = "items")]
        public string Items { get; set; }

        [JsonProperty(PropertyName = "link")]
        public string Link { get; set; }

        [JsonProperty(PropertyName = "imageId")]
        public string ImageId { get; set; }
    }
}