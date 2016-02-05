<?hh // strict
namespace Showcase\Controllers;

use Plenty\Plugin\Controller;
use Plenty\Plugin\Templates\Twig;

class RestController extends Controller
{
	/**
	 *
	 */
	public function showRestModule(Twig $twig, string $moduleName):string
	{
		return $twig->render('PlentyPluginShowcase::rest.'.$moduleName);
	}
}