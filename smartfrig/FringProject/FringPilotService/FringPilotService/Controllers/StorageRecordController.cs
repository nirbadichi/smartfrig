using System.Linq;
using System.Threading.Tasks;
using System.Web.Http;
using System.Web.Http.Controllers;
using System.Web.Http.OData;
using Microsoft.WindowsAzure.Mobile.Service;
using FringPilotService.DataObjects;
using FringPilotService.Models;

namespace FringPilotService.Controllers
{
    public class StorageRecordController : TableController<StorageRecord>
    {
        protected override void Initialize(HttpControllerContext controllerContext)
        {
            base.Initialize(controllerContext);
            FringPilotService1Context context = new FringPilotService1Context();
            DomainManager = new EntityDomainManager<StorageRecord>(context, Request, Services);
        }

        // GET tables/StorageRecord
        public IQueryable<StorageRecord> GetAllStorageRecord()
        {
            return Query(); 
        }

        // GET tables/StorageRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public SingleResult<StorageRecord> GetStorageRecord(string id)
        {
            return Lookup(id);
        }

        // PATCH tables/StorageRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task<StorageRecord> PatchStorageRecord(string id, Delta<StorageRecord> patch)
        {
             return UpdateAsync(id, patch);
        }

        // POST tables/StorageRecord
        public async Task<IHttpActionResult> PostStorageRecord(StorageRecord item)
        {
            StorageRecord current = await InsertAsync(item);
            return CreatedAtRoute("Tables", new { id = current.Id }, current);
        }

        // DELETE tables/StorageRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task DeleteStorageRecord(string id)
        {
             return DeleteAsync(id);
        }

    }
}