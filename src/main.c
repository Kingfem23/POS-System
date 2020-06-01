/*
 Author: Matthew Ajayi
 Date: August 6th 2017
 Purpose: test program.
 
 University of Guelph, 2017.
 CIS*2520 (DE) S17
*/

#include "balancedTreeAPI.h"
#include "posSystem.h"

int main(int argc, char *argv[])
{
	char user[67] = "";
    double total = 0.0;
    double sales  = 0.0;
	FILE * file;
    file = NULL;
    file = fopen(argv[1],"r");
    char name[500];
    Tree * mList;
    mList = createBalancedBinTree(compareFP,destroyFP,copyFP);
    Tree * consumer;
    consumer = createBalancedBinTree(compareFP,destroyFP,copyFP);
    Tree * taxables;
    taxables = createBalancedBinTree(compareFP,destroyFP,copyFP);

    if(argc != 2)
    {
        printf("incorrect arguements\n");
        //printf("\n");
        exit(1);
    }

    if(file == NULL)
    {
        printf("incorrect\n");
        //printf("\n");
        exit(1);
    }

    printf("**************************************************\n");
    printf("Welcome to the POS system!");
    printf("\n");
    printf("**************************************************\n");

    parseFile(file, mList);
    
    do
    {
        //Create Menu
        printf("Press keys:\n1.Search for information about product by name\n2.Add item to customer invoice, by searching its name\n3.Remove a product from inventory.\n4.Edit current customer invoice\n5.Print out inventory\n6.Print out customer invoice\n7.Quit the program and print reports\n");
        scanf(" %[^\t\n]s",user);

        //quit
        if(strcmp(user, "7") == 0)
        {
            printf("**************************************************\n");
            printf("You chose to quit. Thanks for using the program!");
            printf("\n");
            printf("**************************************************\n");
            break;
        }

        //Search for information
        if(strcmp(user, "1") == 0)
        {
            printf("**********************************************************************\n");
            printf("Enter the name of the product you wish to attain information about\n");
            scanf(" %[^\t\n]s",name);
            TreeNode * node = findNode(mList -> root, name, compareFP);
            if(node == NULL)
            {
                printf("The item searched does not exist in our system\n");
                //printf("*************************************************************************************************************************************\n");
                //printf("\n");
                //continue;
            }

            else
            {
                Data * d = (Data*) (node-> data);
                printf("The item you searched for is: %s", d -> iD);
                printf("\n");
                printf("Here is the resulting information");
                printf("\n");
                printf("productID:%s, productName:%s, pub:%s, genre:%s, taxable: %d, quantity: %d, price: %.2f\n", d -> iD, d -> productName, d -> pub, d -> genre, d -> tax, d -> quantity, d -> price);
                
            }

            printf("**********************************************************************\n");

            //printf("\n");
        }

        //add item to invoice by searching it
        if(strcmp(user, "2") == 0)
        {
            printf("**********************************************************************\n");
            printf("Enter the product name that you wish to add to your cart\n");
            scanf(" %[^\t\n]s",name);
            TreeNode * node = findNode(mList -> root, name, compareFP);

            if(node == NULL)
            {
                printf("The item searched could not be added to your invoice\n");
                //printf("**********************************************************************\n");
                //printf("\n");
                //continue;
            }

            else
            {   
                            
                Data * j = (Data*) (node-> data);
                printf("\n");
                printf("The product: %s, has been added to your cart", j -> productName);
                printf("\n");
                printf("Quantities remaining: %d", j -> quantity - 1);
                printf("\n\n");
                
                if(j -> quantity == 0)
                {

                    printf("The value is out of stock\n");
                    //printf("**********************************************************************\n");
                    //printf("\n");
                    //printf("\n");
                    //continue;
                }

                else
                {

                    j -> quantity = j -> quantity - 1;
                
                    Data * m = (Data *) malloc(sizeof(Data));
                    m -> iD = malloc(sizeof(char)* (strlen(j -> iD)) + 1);
                    m -> productName = malloc(sizeof(char)* (strlen(j -> productName)) + 1);
                    m -> pub = malloc(sizeof(char)* (strlen(j -> pub)) + 1);
                    m -> genre = malloc(sizeof(char) * strlen(j -> genre) + 1);
 
                    strcpy(m -> iD, j -> iD);
                    strcpy(m -> productName, j -> productName);
                    strcpy(m -> pub, j -> pub);
                    strcpy(m -> genre, j -> genre);
                    m -> tax = j -> tax;
                    m -> quantity = 1;
                    m -> price = j -> price;

                    //Tax calculation
                    if(j -> tax == 1)
                    {
                        sales = sales + (m -> price * 1.13);
                        treeInsertNode(consumer, m);
                    }
                    //Non Tax calculation
                    if(j -> tax == 0)
                    {
                        total = total + m -> price;
                        treeInsertNode(taxables, m);
                    }

                }
                
            }
            printf("**********************************************************************\n");
            //printf("\n");
        }

        //Delete an item and all its information from inventory
        if(strcmp(user, "3") == 0)
        {
            printf("**********************************************************************\n");

            printf("Enter the product name you wish to delete from the inventory\n");
            scanf(" %[^\t\n]s",name);

            TreeNode * node = findNode(mList -> root, name, compareFP);

            if(node == NULL)
            {
                printf("The item searched could not be deleted\n");
                //printf("*************************************************************************************************************************************\n");
                //printf("\n");
                //continue;
            }

            else
            {   
                treeDeleteNode(mList, name);
                printf("Deleted!\n");
                printf("\n");
                //printf("*************************************************************************************************************************************\n");
                //printf("\n");
            }

            printf("**********************************************************************\n");


        }


        //Edit user invoice
        if(strcmp(user, "4") == 0)
        {
            printf("*************************************************************************************\n");

            printf("Press a to add an item to your invoice\nPress d to delete an item from your invoice\n");
            //char val = '?';
            scanf(" %[^\t\n]s",name);
            printf("\n");
            

            //add to your cart 
            if(strcmp(name, "a") == 0)
            {
                printf("\n");
                printf("Enter the product name that you wish to add to your cart\n");
                scanf(" %[^\t\n]s",name);
                TreeNode * node = findNode(mList -> root, name, compareFP);

                if(node == NULL)
                {
                    printf("The item searched could not be added to your invoice\n");
                    //printf("*************************************************************************************************************************************\n");
                    //printf("\n");
                    //continue;
                }

                else
                {   
       
                    Data * j = (Data*) (node-> data);
                    printf("\n");
                    printf("The product: %s, has been added to your cart", j -> productName);
                    printf("\n");
                    printf("Quantities remaining: %d", j -> quantity - 1);
                    printf("\n\n");

                    if(j -> quantity == 0)
                    {

                        printf("The value is out of stock\n");
                        //printf("*************************************************************************************************************************************\n");
                        //printf("\n");                  
                        //continue;
                    }

                    else
                    {

                        j -> quantity = j -> quantity - 1;
                    
                        Data * m = (Data *) malloc(sizeof(Data));
                        m -> iD = malloc(sizeof(char)* (strlen(j -> iD)) + 1);
                        m -> productName = malloc(sizeof(char)* (strlen(j -> productName)) + 1);
                        m -> pub = malloc(sizeof(char)* (strlen(j -> pub)) + 1);
                        m -> genre = malloc(sizeof(char) * strlen(j -> genre) + 1);


                        strcpy(m -> iD, j -> iD);
                        strcpy(m -> productName, j -> productName);
                        strcpy(m -> pub, j -> pub);
                        strcpy(m -> genre, j -> genre);

                        m -> tax = j -> tax;
                        m -> quantity = 1;
                        m -> price = j -> price;

                        if(j -> tax == 1)
                        {
                            sales = sales + (m -> price * 1.13);
                            treeInsertNode(consumer, m);
                        }

                        if(j -> tax == 0)
                        {
                            total = total + (m -> price * 1.13);
                            treeInsertNode(taxables, m);
                        }

                    }
                    
                }

                

            }

            //delete from the cart
            else if(strcmp(name, "d") == 0)
            {
                printf("\n");
                printf("Enter the product name you wish to delete\n");
                //printf("\n");
                scanf(" %[^\t\n]s",name);

                TreeNode * node = findNode(mList -> root, name, compareFP);

                if(node == NULL)
                {
                    printf("the item searched could not be deleted\n");
                    //printf("*************************************************************************************************************************************\n");
                    //printf("\n");
                    //continue;
                }

                else
                {   
                    treeDeleteNode(consumer, name);
                    treeDeleteNode(taxables, name);

                    Data * d = (Data*)node -> data;

                    d -> quantity = d -> quantity + 1;

                    //Tax calculation
                    if(d -> tax == 1)
                    {
                        sales = sales - (d -> price * 1.13);
                        // treeInsertNode(consumer, d);
                    }
                    //Non Tax calculation
                    if(d -> tax == 0)
                    {
                        total = total- (d -> price);
                        //treeInsertNode(taxables, d);
                    }


                    printf("Deleted!\n");
                    //printf("\n");
                }
            }

            else
            {
                printf("You entered an incorrect value, try again");
                //printf("\n");
                //continue;
            }

            printf("*************************************************************************************\n");
            //printf("\n");
        }

        //print store inventory
        else if(strcmp(user, "5") == 0)
        {
            printf("\n");
            //printf("Store copy\n");
            printf("**************************************\n");  
            printf("Store copy\n");
            //printf("\n");
            treeInOrderPrint(mList,printNodeFP);
            printf("**************************************\n");  
            //printf("\n");
        }

        //print consumer invoice
        else if(strcmp(user, "6") == 0)
        {
            //printf("Consumer copy\n");
            printf("**************************************\n");  
            printf("Consumer copy\n");
            printf("\n");
            printf("Taxables");
            printf("\n");
            treeInOrderPrint(consumer, printNodeFP);
            printf("\n");
            printf("Non-Taxables");
            printf("\n");
            treeInOrderPrint(taxables, printNodeFP);
            printf("\n");
            printf("Your taxables total is: %.2f\n", sales);
            printf("Your non taxables total is: %.2f\n", total);
            printf("**************************************\n");  
            //printf("\n");
        }

        printf("\n");
        // else
        // {
        //     printf("*************************************************************************************************************************************\n");

        //     printf("You entered an incorrect value, please try again");
        //     printf("\n");

        //     printf("*************************************************************************************************************************************\n");
        //     printf("\n");
        //     //continue;
        // }

    }while(strcmp(user, "7") != 0);


    printf("\n");
    printf("Final Store copy\n");
    printf("**************************************\n");  
    printf("\n");
    treeInOrderPrint(mList,printNodeFP);
    printf("\n");

    printf("Final Consumer copy\n");
    printf("**************************************\n");  
    printf("\n");
    printf("Taxables");
    printf("\n");
    treeInOrderPrint(consumer, printNodeFP);
    printf("\n");
    printf("Non-Taxables");
    printf("\n");
    treeInOrderPrint(taxables, printNodeFP);
    printf("\n");
    printf("Your taxables total is: %.2f\n", sales);
    printf("Your non-taxables total is: %.2f\n", total);
    printf("\n");
  
    printf("\n\n");
    fclose(file);
}

