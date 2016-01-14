<?hh //strict

namespace Showcase\Controllers;

use Plenty\Plugin\Controller;
use Plenty\Modules\Item\Producer\Models\Producer;
use Plenty\Plugin\Http\Request;
use Plenty\Plugin\Templates\Twig;
use Plenty\Plugin\ConfigRepository;

use Plenty\Modules\Item\DataLayer\Contracts\ItemDataLayerRepositoryContract;
use Plenty\Modules\Category\Contracts\CategoryRepository;

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

	public function showItemView(Twig $twig, CategoryRepository $categoryRepo, ItemDataLayerRepositoryContract $itemRepo, string $spacer = "", string $itemId = ""):string
	{
		$categoryTree = $categoryRepo->getSitemapTree('de');
		$item = $itemRepo->search(	Map{'itemDescription'=>['name1','itemId','lang','urlContent', 'description'], 'variationImageList'=>['path']}, 
									Map{'itemBase.hasId'=>['itemId'=>$itemId], 'variationBase.isPrimary?' => []}, 
									Map{'language'=>'de'}
								);
		
		$templateData = Map{'item' => $item->current(), 'categoryTree' => $categoryTree};

		return $twig->render('PlentyPluginShowcase::content.ItemView', $templateData);
	}

	public function showCategory(Twig $twig, CategoryRepository $categoryRepo, ItemDataLayerRepositoryContract $itemRepo, string $level1, ?string $level2 = null, ?string $level3 = null, ?string $level4 = null, ?string $level5 = null, ?string $level6 = null):string
	{
		$categoryTree = $categoryRepo->getSitemapTree('de');
		$category = $categoryRepo->findCategoryByUrl($level1, $level2, $level3, $level4, $level5, $level6);
		$categoryId = 0;
		if ($category != null)
		{
			$categoryId = $category->plenty_category_id;
		}

		$items = $itemRepo->search(	Map{'itemDescription'=>['name1','itemId','lang','urlContent']}, 
									Map{'variationCategory.hasCategory'=>['categoryId'=>$categoryId], 'variationBase.isPrimary?' => []}, 
									Map{'language'=>'de'}
								);

		$templateData = Map{'categoryTree' => $categoryTree, 'items' => $items};

		return $twig->render('PlentyPluginShowcase::content.CategoryView', $templateData);
	}
}