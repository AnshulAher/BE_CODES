// SPDX-License-Identifier: UNLICENCE
pragma solidity ^0.8.0;

contract Bank{

    address public accHolder;
    uint256 balance = 0;

    constructor(){
        accHolder = msg.sender;
    }

      function withdraw(uint256 amount) public {
        require(amount > 0, "Withdrawal amount should be greater than 0.");
        require(balance >= amount, "Insufficient account balance.");
        require(msg.sender == accHolder, "You are not the account owner.");

        payable(msg.sender).transfer(amount);
        balance -= amount;
    }

    function deposit() public payable {
        require(msg.value>0,"Deposit amount should be greater than 0.");
        require(msg.sender==accHolder,"You are not the account owner.");
        balance = balance + msg.value;
    }

    function showBalance() public view returns(uint) {
        require(msg.sender==accHolder,"You are not the account owner.");
        return balance;
    }
}