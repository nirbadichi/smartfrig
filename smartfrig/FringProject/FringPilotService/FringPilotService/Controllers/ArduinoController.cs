using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using Microsoft.WindowsAzure.Mobile.Service;
using Microsoft.WindowsAzure.MobileServices;
using System.Threading.Tasks;
using FringPilotService.DataObjects;

namespace FringPilotService.Controllers
{
    public class ArduinoController : ApiController
    {
        const string applicationURL = @"http://fringpilotservice.azure-mobile.net";
        const string applicationKey = @"lIbRNBgZYLkUENaNSNmvLHwoWUyvwY11";
        MobileServiceClient client;
        IMobileServiceTable<StorageRecord> storageTable;
        IMobileServiceTable<ItemsRecord> itemsTable;
        public List<StorageRecord> storageRecords { get; private set; }
        public List<ItemsRecord> itemsRecords { get; private set; }

        public ArduinoController()
        {

            // Initialize the Mobile Service client with your URL and key
            client = new MobileServiceClient(applicationURL, applicationKey);

            // Create an MSTable instance to allow us to work with the StorageItem table
            storageTable = client.GetTable<StorageRecord>();

            // Create an MSTable instance to allow us to work with the AllItems table
            itemsTable = client.GetTable<ItemsRecord>();
        }
        public ApiServices Services { get; set; }

        // GET api/Arduino
        public string Get()
        {
            Services.Log.Info("Hello from custom controller!");
            return "Hello";
        }

        // async public Task<List<DataObjects.StorageItem>> PostProcessTag(string Id)
        async public Task<string> PostProcessTag(string itemId,string frigId)
        {
            try
            {
                // This code refreshes the entries in the list view by querying the TodoItems table.
                // The query excludes completed TodoItems
                storageRecords = await storageTable
                    .Where(storageRecord => storageRecord.ItemId == itemId && storageRecord.FrigId == frigId).ToListAsync();
                if (storageRecords.Count > 0)
                {
                    await storageTable.DeleteAsync(storageRecords[0]);
                    return "delete";
                }
                else
                {
                    itemsRecords = await itemsTable
                    .Where(itemsRecord => itemsRecord.Id == itemId).ToListAsync();
                    if (itemsRecords.Count > 0)
                    {
                        StorageRecord newItem = new StorageRecord();
                        newItem.ItemId = itemId;
                        newItem.FrigId = frigId;
                        await storageTable.InsertAsync(newItem);
                        return "insert";
                    }
                    return "Item doesn't exist";
                }
            }
            catch (MobileServiceInvalidOperationException e)
            {
                Console.Error.WriteLine(@"ERROR {0}", e.Message);
                return null;
            }

        }
    }
}
