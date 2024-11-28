#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/common/io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/PolygonMesh.h>
#include <pcl/common/common.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <omp.h>

int main() {
    pcl::NormalEstimationOMP<pcl::PointXYZ, pcl::Normal> ne; // Multi Thread
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    ne.setSearchMethod (tree);
    // ne.setInputCloud (cloud);
    // ne.setKSearch (20);
    // ne.setViewPoint (0.0f, 0.0f, 0.0f); // Not useful
    // ne.setNumberOfThreads(4);
    // ne.compute(*normals);


    omp_set_num_threads(2);

    #pragma omp parallel for ordered schedule(dynamic) 
    for(size_t i = 0; i < 4; i++) //jobs is a vector
    {
        #pragma omp ordered
        std::cout << i << "\t" << omp_get_thread_num() << "\t" << omp_get_num_threads() << "\t" << omp_in_parallel() << std::endl;
    }
     return 0;    

    // should be
    // 0 0 2 1
    // 1 1 2 1
    // 2 0 2 1
    // 3 1 2 1     
}



    // #pragma omp parallel
    // {
    //     printf("Hello from process: %d\n", omp_get_thread_num());
    // }
    // return 0;

    // std::cout << "Before setting threads:\n";
    // #pragma omp parallel
    // {
    //     #pragma omp single // To print only once per parallel region
    //     std::cout << "omp_get_num_threads(): " << omp_get_num_threads() << std::endl;
    // }

    // // Set number of threads to 4
    // omp_set_num_threads(4);

    // std::cout << "After setting threads:\n";
    // #pragma omp parallel
    // {
    //     #pragma omp single // To print only once per parallel region
    //     std::cout << "omp_get_num_threads(): " << omp_get_num_threads() << std::endl;
    // }


    // omp_set_num_threads(8);
    // std::cout << "omp_get_num_threads(): " << omp_get_num_threads() << std::endl;

    // int counter = 0;
    // #pragma omp parallel for num_threads(8)
    // for (int i=0; i<100; i++){
    //     #pragma omp critical
    //     {
    //         std::cout << "thread id: " << omp_get_thread_num() << std::endl;
    //         counter++;
    //     }
    // }

    // return 0;
