# Access Key Creation

## Summary
This rule detects any attempt to create an access key, another lambda function disables this key at the same time.

## Data Source
- AWS CloudTrail (CloudWatch Logs: /cloudsoc/cloudtrail)

## Detection Logic
**Metric Filter Pattern**
```text
{ $.eventName = "CreateAccessKey" }
