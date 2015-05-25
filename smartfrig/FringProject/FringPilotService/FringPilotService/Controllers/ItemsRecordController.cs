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
    public class ItemsRecordController : TableController<ItemsRecord>
    {
        protected override void Initialize(HttpControllerContext controllerContext)
        {
            base.Initialize(controllerContext);
            FringPilotServiceContext context = new FringPilotServiceContext();
            DomainManager = new EntityDomainManager<ItemsRecord>(context, Request, Services);
        }

        // GET tables/ItemsRecord
        public IQueryable<ItemsRecord> GetAllItemsRecord()
        {
            return Query(); 
        }

        // GET tables/ItemsRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public SingleResult<ItemsRecord> GetItemsRecord(string id)
        {
            return Lookup(id);
        }

        // PATCH tables/ItemsRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task<ItemsRecord> PatchItemsRecord(string id, Delta<ItemsRecord> patch)
        {
             return UpdateAsync(id, patch);
        }

        // POST tables/ItemsRecord
        public async Task<IHttpActionResult> PostItemsRecord(ItemsRecord item)
        {
            ItemsRecord current = await InsertAsync(item);
            return CreatedAtRoute("Tables", new { id = current.Id }, current);
        }

        // DELETE tables/ItemsRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task DeleteItemsRecord(string id)
        {
             return DeleteAsync(id);
        }

    }
}