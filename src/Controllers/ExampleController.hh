<?hh //strict

namespace Showcase\Controllers;

use Plenty\Plugin\Controller;
use Plenty\Plugin\Templates\Twig;

use Plenty\Modules\Category\Contracts\CategoryRepository;
use Plenty\Modules\Category\Models\Category;

class ExampleController extends Controller
{
    public function showBasicExamples( Twig $twig ):string
    {
        return $twig->render('PlentyPluginShowcase::content.Basics');
    }

    public function showCategoryExamples(
        Twig $twig,
        CategoryRepository $categoryRepository,
        ?string $lvl1 = null,
        ?string $lvl2 = null,
        ?string $lvl3 = null,
        ?string $lvl4 = null,
        ?string $lvl5 = null,
        ?string $lvl6 = null
        ):string
    {
        $categoryList = $categoryRepository->getSitemapList();
        $categoryTree = $categoryRepository->getSitemapTree();

        $currentCategory = null;
        if( $lvl1 !== null )
        {
            $currentCategory = $categoryRepository->findCategoryByUrl( $lvl1, $lvl2, $lvl3, $lvl4, $lvl5, $lvl6 );
        }

        $templateData = array(
            'categoryList' => $categoryList,
            'categoryTree' => $categoryTree,
            'currentCategory' => $currentCategory
        );

        return $twig->render('PlentyPluginShowcase::content.Categories', $templateData);
    }
}