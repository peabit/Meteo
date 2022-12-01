using Microsoft.AspNetCore.Mvc;

namespace Meteo.Controllers
{
    [Route("/")]
    public class FrontendController : Controller
    {
        public IActionResult Index() => View();
    }
}