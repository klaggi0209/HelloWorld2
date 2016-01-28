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

    public function showCategoryExamples( Twig $twig, CategoryRepository $categoryRepository ):string
    {
        $categoryTree = $categoryRepository->getSitemapTree( 'de' );

        $templateData = array(
            'categories' => $categoryTree
        );

        return $twig->render('PlentyPluginShowcase::content.Categories', $templateData);
    }
}