using System.Linq;
using System.Threading.Tasks;
using System.Web.Http;
using System.Web.Http.Controllers;
using System.Web.Http.OData;
using Microsoft.WindowsAzure.Mobile.Service;
using FringProjectMobileService.DataObjects;
using FringProjectMobileService.Models;

namespace FringProjectMobileService.Controllers
{
    public class StorageItemController : TableController<StorageItem>
    {
        protected override void Initialize(HttpControllerContext controllerContext)
        {
            base.Initialize(controllerContext);
            FringProjectMobileServiceContext context = new FringProjectMobileServiceContext();
            DomainManager = new EntityDomainManager<StorageItem>(context, Request, Services);
        }

        // GET tables/StorageItem
        public IQueryable<StorageItem> GetAllStorageItem()
        {
            return Query(); 
        }

        // GET tables/StorageItem/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public SingleResult<StorageItem> GetStorageItem(string id)
        {
            return Lookup(id);
        }

        // PATCH tables/StorageItem/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task<StorageItem> PatchStorageItem(string id, Delta<StorageItem> patch)
        {
             return UpdateAsync(id, patch);
        }

        // POST tables/StorageItem
        public async Task<IHttpActionResult> PostStorageItem(StorageItem item)
        {
            StorageItem current = await InsertAsync(item);
            return CreatedAtRoute("Tables", new { id = current.Id }, current);
        }

        // DELETE tables/StorageItem/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task DeleteStorageItem(string id)
        {
             return DeleteAsync(id);
        }

    }
}