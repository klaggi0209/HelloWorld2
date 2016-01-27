<?hh //strict

namespace Showcase\Controllers;

use Plenty\Plugin\Controller;
use Plenty\Modules\Item\Producer\Models\Producer;
use Plenty\Plugin\Http\Request;
use Plenty\Plugin\Templates\Twig;
use Plenty\Plugin\ConfigRepository;

use Plenty\Modules\Item\DataLayer\Contracts\ItemDataLayerRepositoryContract;
use Plenty\Modules\Category\Contracts\CategoryRepository;
use Plenty\Modules\Category\Models\Category;

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

		$columns = [
			'itemDescription' => [
				'name1',
				'itemId',
				'lang',
				'urlContent',
				'description'
			],
			'variationRetailPrice' => [
				'price'
			],
			'variationImageList' => [
				'path'
			],
			'variationBase' => [
				'customNumber',
			]
		];

		$filter = [
			'itemBase.hasId' => [
				'itemId' => $itemId
			],
			'variationBase.isPrimary?' => []
		];

		$params = [
			'language' => 'de'
		];

		$item = $itemRepo->search($columns, $filter, $params);

		$templateData = ['item' => $item->current(), 'categoryTree' => $categoryTree];

		return $twig->render('PlentyPluginShowcase::content.ItemView', $templateData);
	}

	public function showCategory(Twig $twig, CategoryRepository $categoryRepo, ItemDataLayerRepositoryContract $itemRepo, string $level1, ?string $level2 = null, ?string $level3 = null, ?string $level4 = null, ?string $level5 = null, ?string $level6 = null):string
	{
		$categoryTree = $categoryRepo->getSitemapTree('de');
		$category = $categoryRepo->findCategoryByUrl($level1, $level2, $level3, $level4, $level5, $level6);

		$categoryFilter = $this->getCategoryFilter($categoryRepo, $category);

		$columns = [
			'itemDescription' => [
				'name1',
				'itemId',
				'lang',
				'urlContent'
			],
			'variationRetailPrice' => [
				'price'
			],
			'variationImageList' => [
				'path'
			],
		];

		$filter = [
			'variationBase.isPrimary?' => []
		];

		if(count($categoryFilter))
		{
			$filter['variationCategory.hasCategoryBranch'] = $categoryFilter;
		}

		$params = [
			'language' => 'de'
		];

		$items = $itemRepo->search($columns, $filter, $params);

		$templateData = ['categoryTree' => $categoryTree, 'items' => $items];

		if ($level1 == null)
		{
			$templateData['navigationHome'] = 'true';
		}

		return $twig->render('PlentyPluginShowcase::content.CategoryView', $templateData);
	}

	private function getCategoryFilter(CategoryRepository $categoryRepo, ?Category $category):array<string,int>
	{
		$categoryId = 0;

		$categoryFilter = [];

		if ($category != null)
		{
			$categoryId = $category->plenty_category_id;
			$categoryLevel = $category->plenty_category_level;

			$categoryFilter = [
				'category1' => 0,
				'category2' => 0,
				'category3' => 0,
				'category4' => 0,
				'category5' => 0,
				'category6' => 0,
			];
			
			$categoryFilter['category'.$categoryLevel] = $category->plenty_category_id;
			$parentCategoryId = $category->plenty_category_parent_category_id;

			for($level = $categoryLevel; $level > 1 && $category != null; $level--)
			{
				$category = $categoryRepo->get($parentCategoryId, 'de');

				if ($category != null)
				{
					$categoryFilter['category'.$category->plenty_category_level] = $category->plenty_category_id;
					$parentCategoryId = $category->plenty_category_parent_category_id;
				}
			}
		}

		return $categoryFilter;
	}

	public function showCaption(Twig $twig, string $caption):string
	{
		
		return $twig->render('PlentyPluginShowcase::content.' . $caption );
	}
	 
}
