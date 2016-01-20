<?hh // strict
namespace Showcase\Providers;

use Plenty\Plugin\ServiceProvider;
use Plenty\Plugin\Templates\Twig;

class ShowcaseServiceProvider extends ServiceProvider
{
	public function register():void
	{
		$this->getApplication()->register(\Showcase\Providers\ShowcaseRouteServiceProvider::class);
	}

	public function boot(Twig $twig):void
	{
		$twig->addExtension('Twig_Extensions_Extension_Intl');
	}
}
