<?hh // strict
namespace Showcase\Providers;

use Plenty\Plugin\RouteServiceProvider;
use Plenty\Plugin\Routing\Router;

class ShowcaseServiceProvider extends RouteServiceProvider
{
	/**
	 * 
	 */
	public function register():void
	{
	}

	/**
	 * 
	 */
	public function map(Router $router):void
	{
		$router->get('showcase', 'Showcase\Controllers\ContentController@landingPage');
	}
}