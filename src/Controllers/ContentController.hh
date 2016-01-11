<?hh //strict

namespace Showcase\Controllers;

use Plenty\Plugin\Controller;
use Plenty\Modules\Item\Producer\Models\Producer;
use Plenty\Plugin\Http\Request;
use Plenty\Plugin\Templates\Twig;
use Plenty\Plugin\ConfigRepository;

use Plenty\Modules\Item\DataLayer\Contracts\ItemDataLayerRepositoryContract;

/**
 * Class ContentController
 * @package Showcase\Controllers
 */
class ContentController extends Controller
{
	public function landingPage(Twig $twig):string
	{
		return $twig->render('PlentyPluginShowcase::content.LandingPage');
	}
}