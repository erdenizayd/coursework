#include "SocialNetwork.h"

#include <iostream>

SocialNetwork::SocialNetwork() {

}

void SocialNetwork::addProfile(const std::string &firstname, const std::string &lastname, const std::string &email) {
    Profile newprofile = Profile(firstname, lastname, email);
    profiles.insertSorted(newprofile);
    
}

void SocialNetwork::addPost(const std::string &message, const std::string &email) {
    Post newpost = Post(message);
    posts.insertAtTheTail(newpost);
    Node<Profile> *current = profiles.getFirstNode();
    while(current->data.getEmail() != email){
        current = current->next;
    }
    (current->data.getPosts()).insertAtTheTail(&(posts.getLastNode()->data));
}

void SocialNetwork::deleteProfile(const std::string &email) {
    Node<Profile> *curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email) curr = curr->next;

    Node<Post*> *post = curr->data.getPosts().getFirstNode();
    while(post != nullptr){
        post = unFriend(post);
    }
    
    Node<Profile*> *friends = curr->data.getFriends().getFirstNode();
    
    while(friends != nullptr){
        friends->data->getFriends().removeNode(&(curr->data));
        friends = friends->next;
    }
    
    
    profiles.removeNode(curr->data);
    
}


Node<Post*> * SocialNetwork::unFriend(Node<Post*> *post){
    Node<Profile> *curr = profiles.getFirstNode();
    Node<Post*> *next;
    int id = (post->data)->getPostId();
    while(curr != nullptr){
        unlikePost(id, curr->data.getEmail());
        curr = curr->next;
    }
    next = post->next;
    posts.removeNode(*(post->data));
    return next;
}

void SocialNetwork::makeFriends(const std::string &email1, const std::string &email2) {
    Node<Profile> *curr1 = profiles.getFirstNode();
    Node<Profile> *curr2 = curr1;
    while(curr1->data.getEmail() != email1){
        curr1 = curr1->next;
    }
    while(curr2->data.getEmail() != email2){
        curr2 = curr2->next;
    }
    
    curr1->data.getFriends().insertAtTheTail(&(curr2->data));
    curr2->data.getFriends().insertAtTheTail(&(curr1->data));
}

void SocialNetwork::likePost(int postId, const std::string &email) {
    Node<Profile> *curr1 = profiles.getFirstNode();
    Node<Post> *curr2  = posts.getFirstNode();
    while(curr1->data.getEmail() != email){
        curr1 = curr1->next;
    }    
    
    while(curr2->data.getPostId() != postId){
        curr2 = curr2->next;
    }
    curr1->data.getLikes().insertAtTheTail(&(curr2->data));
}

void SocialNetwork::unlikePost(int postId, const std::string &email) {
    Node<Profile> *curr1 = profiles.getFirstNode();
    Node<Post> *curr2  = posts.getFirstNode();
    while(curr1->data.getEmail() != email){
        curr1 = curr1->next;
    }    
    
    while(curr2->data.getPostId() != postId){
        curr2 = curr2->next;
    }
    curr1->data.getLikes().removeNode(&(curr2->data));
}

LinkedList<Profile *> SocialNetwork::getMutualFriends(const std::string &email1, const std::string &email2) {
    LinkedList<Profile*> newlist = LinkedList<Profile*>();
    Node<Profile*> *first;
    LinkedList<Profile*> second;
    Node<Profile> *curr1 = profiles.getFirstNode();
    Node<Profile> *curr2 = profiles.getFirstNode();
    while(curr1->data.getEmail() != email1){
        curr1 = curr1->next;
    }
    while(curr2->data.getEmail() != email2){
        curr2 = curr2->next;
    }
    first = curr1->data.getFriends().getFirstNode();
    second = curr2->data.getFriends();
    
    if(curr1->data.getFriends().isEmpty() || second.isEmpty()) return newlist;
    
    while((first != nullptr)){
        if(isFriend(second,first)){
            newlist.insertAtTheTail(first->data);
        }
        first = first->next;
    }
    return newlist;
}

bool SocialNetwork::isFriend(LinkedList<Profile*> user, Node<Profile *> *fp){
    Node<Profile*> *curr = user.getFirstNode();
    while(curr != nullptr){
        if(curr->data == fp->data) return true;
        curr = curr->next;
    }
    return false;
}

LinkedList<Post *> SocialNetwork::getListOfMostRecentPosts(const std::string &email, int k) {
    LinkedList<Post*> newlist = LinkedList<Post*>();
    Node<Profile> *curr = profiles.getFirstNode();
    Node<Post*> *post;
    int i = k;
    
    while(curr->data.getEmail() != email){
        curr = curr->next;
    }
    
    post = curr->data.getPosts().getLastNode();
    
    while((post != nullptr) && (i != 0)){
        newlist.insertAtTheTail(post->data);
        post = post->prev;
        i--;
    }
    
    return newlist;
}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}

