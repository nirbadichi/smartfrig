using Microsoft.WindowsAzure.Mobile.Service;
using System;
using Newtonsoft.Json;

namespace FringPilotService.DataObjects
{
    public class StorageRecord : EntityData
    {
        [JsonProperty(PropertyName = "frigId")]
        public string FrigId { get; set; }

        [JsonProperty(PropertyName = "itemId")]
        public string ItemId { get; set; }
    }
}