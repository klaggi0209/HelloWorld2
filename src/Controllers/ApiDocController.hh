<?hh // strict
namespace Showcase\Controllers;

use Plenty\Plugin\Controller;
use Plenty\Plugin\Templates\Twig;

class ApiDocController extends Controller
{
	/**
	 *
	 */
	public function showApiDoc(Twig $twig):string
	{

		return $twig->render('PlentyPluginShowcase::api.classes');
}

	public function showApiModule(Twig $twig, string $module):string
	{
		return $twig->render('PlentyPluginShowcase::api.Modules.' . $module . '.classes');
	}

}