# IAMEnumeration

## Summary
Flags any IAM user who attempts a modofiable count of enumeration commands in a modifiable amount of time.

## Data Source
- AWS CloudTrail (CloudWatch Logs: /cloudsoc/cloudtrail)

## Detection Logic
**Metric Filter Pattern**
```text
{($.eventName = "ListUsers") || ($.eventName = "ListRoles") || ($.eventName = "GetAccountAuthorizationDetails") }
