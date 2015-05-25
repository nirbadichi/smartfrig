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
    public class RecipeRecordController : TableController<RecipeRecord>
    {
        protected override void Initialize(HttpControllerContext controllerContext)
        {
            base.Initialize(controllerContext);
            FringPilotService2Context context = new FringPilotService2Context();
            DomainManager = new EntityDomainManager<RecipeRecord>(context, Request, Services);
        }

        // GET tables/RecipeRecord
        public IQueryable<RecipeRecord> GetAllRecipeRecord()
        {
            return Query(); 
        }

        // GET tables/RecipeRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public SingleResult<RecipeRecord> GetRecipeRecord(string id)
        {
            return Lookup(id);
        }

        // PATCH tables/RecipeRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task<RecipeRecord> PatchRecipeRecord(string id, Delta<RecipeRecord> patch)
        {
             return UpdateAsync(id, patch);
        }

        // POST tables/RecipeRecord
        public async Task<IHttpActionResult> PostRecipeRecord(RecipeRecord item)
        {
            RecipeRecord current = await InsertAsync(item);
            return CreatedAtRoute("Tables", new { id = current.Id }, current);
        }

        // DELETE tables/RecipeRecord/48D68C86-6EA6-4C25-AA33-223FC9A27959
        public Task DeleteRecipeRecord(string id)
        {
             return DeleteAsync(id);
        }

    }
}