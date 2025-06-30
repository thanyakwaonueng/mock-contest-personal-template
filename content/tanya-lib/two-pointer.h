/**
 * Author: Tanya
 * Description: TODO
 */

void two_pointer_template(){
    //TODO:initialize array a
    //check all valid subsegment ended at a[i]
    //move i by 1, if invalid shrink till valid, then check in next iteration
    //pass edge case when i = n-1
    for(int i=-1,j=0;i<n;){
        if(i>=0){
            if(a[i] == 1)++one_cnt;
            else ++zero_cnt;
        } 

        if(zero_cnt <= k){ //cal valid state
            int cost = i-j+1;
            if(cost > local_max){
                local_max = cost;
                id = j;
            }
        } else { //shrink till valid
            while(zero_cnt > k){
                if(a[j] == 1)--one_cnt;
                else --zero_cnt;
                ++j;
            }
        }
        ++i;
    }

} //end two_pointer template
