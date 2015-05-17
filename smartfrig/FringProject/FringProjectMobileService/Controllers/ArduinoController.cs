using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using Microsoft.WindowsAzure.Mobile.Service;
//using Common;

namespace FringProjectMobileService.Controllers
{
    public class ArduinoController : ApiController
    {
        public ApiServices Services { get; set; }

        // GET api/Arduino
        public string Get()
        {
            Services.Log.Info("Hello from custom controller!");
            return "Hello";
        }


        public string GetProcessTag(String id)
        {
            return id;
        }
        /*public async void GetProcessTag(String id)
        {
            DataObjects.StorageItem new_record = new DataObjects.StorageItem();
            new_record.Id = "new ID 1";
            new_record.Image_id = "new Image 2";
            new_record.Name = "new Name nir";
            new_record.Quantity = 2;
            new_record.Type = "new Type";
            IMobileServiceClient MobileService = new MobileServiceClient("https://fringmobileservice.azure-mobile.net/");
            IMobileServiceTable<DataObjects.StorageItem> table = MobileService.GetTable<DataObjects.StorageItem>();
            await table.InsertAsync(new_record);

        }*/
    }
}
